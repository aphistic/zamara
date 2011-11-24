#include <fstream>
#include <iostream>
#include <string.h>

#include "zamara/mpq/mpq.h"
#include "zamara/mpq/mpq_block_encryptor.h"
#include "zamara/endian/endian.h"
#include "zamara/mpq/mpq_compression.h"
#include "zamara/exception/zamara_exception.h"

using zamara::endian::Endian;
using zamara::exception::ZamaraException;

namespace zamara {
  namespace mpq {

Mpq::Mpq(std::string file_path) {
  user_data_ = 0;
  file_path_ = file_path;
}

Mpq::~Mpq() {
  delete user_data_;

  if (IsLoaded()) {
    Close();
  }
}

void Mpq::Load(std::string file_path) {
  file_path_ = file_path;
  Load();
}

void Mpq::Load() {
  if (IsLoaded()) {
    Close();
  }
  file_.open(file_path_.c_str(), std::ios::in | std::ios::binary);

  if (!IsLoaded()) {
    throw ZamaraException("Could not find file.",
                          ZamaraException::FILE_NOT_FOUND);
  }

  ReadHeader();
  ReadHashTable();
  ReadBlockTable();
  ReadFiles();
}

void Mpq::Close() {
  if (file_ != NULL) {
    file_.close();
  }
}

bool Mpq::IsLoaded() {
    if (file_) {
        return file_.is_open();
    }
    return false;
}

MpqFile Mpq::GetFile(std::string filename) {
  for (uint32_t idx = 0; idx < files().size(); idx++) {
    if (files()[idx].filename() == filename)
    {
      return files()[idx];
    }
  }

  throw ZamaraException("File not found in MPQ archive.",
                        ZamaraException::MPQ_FILE_NOT_FOUND);
}

MpqHeader Mpq::header() {
  return header_;
}

MpqUserData* Mpq::user_data() {
  return user_data_;
}

std::vector<MpqFile> Mpq::files() {
  return files_;
}

MpqHashEntry* Mpq::GetHashEntry(std::string filename) {
  uint32_t hash_a = MpqBlockEncryptor::HashString(filename, 0x100);
  uint32_t hash_b = MpqBlockEncryptor::HashString(filename, 0x200);

  for (uint32_t idx = 0; idx < header().hash_table_entries; idx++) {
    if (hash_table_[idx].file_path_hash_a() == hash_a &&
        hash_table_[idx].file_path_hash_b() == hash_b) {
      return &hash_table_[idx];      
    }
  }

  return NULL;
}

bool Mpq::HasUserData() {
  if (user_data_) {
    return true;
  }
  return false;
}

void Mpq::ReadHeader() {
  // A buffer big enough to read up to 64 bits of data
  char* buffer = new char[8];
  
  file_.read(buffer, 4);
  if (strncmp(buffer, "MPQ", 3)) { // Check that the file starts with "MPQ"
    // Free the buffer before we leave
    delete [] buffer;

    Close();
    throw ZamaraException("File is not an MPQ.",
                ZamaraException::FILE_NOT_MPQ);
  }

  if (buffer[3] == 0x1B) {
    // This is the user data portion of the file.
    
    uint32_t user_header_size;
    uint32_t user_archive_size;

    // Header Size
    file_.read(buffer, 4);
    user_header_size = Endian::LeToH32(*(reinterpret_cast<uint32_t*>(buffer)));

    // Archive Size
    file_.read(buffer, 4);
    user_archive_size = Endian::LeToH32(*(reinterpret_cast<uint32_t*>(buffer)));

    file_.seekg(0, std::ios::beg);
    
    char* user_buffer = new char[user_archive_size];

    file_.read(user_buffer, user_archive_size);

    user_data_ = new MpqUserData(user_buffer);

    file_.read(buffer, 4);

    delete [] user_buffer;
  }

  // Header Size
  file_.read(buffer, 4);
  header_.header_size = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer)));

  delete [] buffer;

  // Make a new buffer to read the rest of the header
  buffer = new char[header_.header_size - 4];  // Already read 4 bytes of header
  file_.read(buffer, header_.header_size - 4);

  // Archive Size
  header_.archive_size = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer)));

  header_.format_version = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 0x04)));
  
  header_.block_size = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 0x06)));

  header_.hash_table_offset = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 0x08)));

  header_.block_table_offset = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 0x0C)));

  header_.hash_table_entries = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 0x10)));
  
  header_.block_table_entries = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 0x14)));

  header_.extended_block_table_offset = Endian::LeToH64(
      *(reinterpret_cast<uint64_t*>(buffer + 0x18)));
  
  header_.hash_table_offset_high = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 0x20)));

  header_.block_table_offset_high = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 0x22)));

  archive_offset_ = 0x00;
  if (HasUserData())
  {
    archive_offset_ = user_data()->header().archive_offset;  
  }

  delete [] buffer;
}

void Mpq::ReadHashTable() {
  uint32_t hash_entries = header().hash_table_entries;

  hash_table_.clear();

  file_.seekg(archive_offset_ +
              header().hash_table_offset, std::ios::beg);
  
  // Each entry is the size of 4x uint32_t's, giving
  // 16 bytes.  Read a buffer big enough for the entire hash table
  // and then decrypt it
  char* buffer = new char[hash_entries * 16];

  file_.read(buffer, hash_entries * 16);

  MpqBlockEncryptor encryptor("(hash table)", 0x300,
                              reinterpret_cast<uint32_t*>(buffer),
                              hash_entries * 16);
  encryptor.Decrypt();

  for (uint32_t idx = 0; idx < hash_entries; idx++) {
    MpqHashEntry entry;
    entry.Load(buffer + (idx * 16));
    hash_table_.push_back(entry);
  }

  delete [] buffer;
}

void Mpq::ReadBlockTable() {
  uint32_t block_entries = header().block_table_entries;

  block_table_.clear();

  file_.seekg(archive_offset_ +
              header().block_table_offset, std::ios::beg);

  // Same as the hash table, each entry is the size of 4x
  // uint32_t.
  char* buffer = new char[block_entries * 16];
  
  file_.read(buffer, block_entries * 16);

  MpqBlockEncryptor encryptor("(block table)", 0x300,
                              reinterpret_cast<uint32_t*>(buffer),
                              block_entries * 16);
  encryptor.Decrypt();

  for (uint32_t idx = 0; idx < block_entries; idx++) {
    MpqBlockEntry entry;
    entry.Load(buffer + (idx * 16));
    block_table_.push_back(entry);
  }

  delete [] buffer;
}

void Mpq::ReadFiles() {
  MpqHashEntry* list = GetHashEntry("(listfile)");

  if (list != NULL) {
    MpqBlockEntry block = block_table_[list->block_index()];

    char* in_buffer = new char[block.compressed_size()];
    char* out_buffer = new char[block.file_size()];

    file_.seekg(archive_offset_ + block.file_position(), std::ios::beg);
    file_.read(in_buffer, block.compressed_size());

    MpqCompression::DecompressBzip2(in_buffer, block.compressed_size(),
                                    out_buffer, block.file_size());

    std::string files(out_buffer, block.file_size());

    // Clear out any files from a previously loaded MPQ
    files_.clear();

    int file_index = 0;
    uint32_t file_position = 0;
    while (file_position < files.length())
    {
      size_t name_end = files.find("\r\n", file_position);
      std::string filename = files.substr(file_position,
                                          name_end - file_position);
      MpqHashEntry* hash_entry = GetHashEntry(filename);

      if (hash_entry != NULL)
      {
        MpqFile file(&file_, archive_offset_);
        file.Load(filename, hash_entry,
                  &(block_table_[hash_entry->block_index()]));
        files_.push_back(file);
      }
                                      
      file_position = name_end + 2;
      file_index++;
    }
    
    delete [] in_buffer;
    delete [] out_buffer;
  }
}

  }
}
