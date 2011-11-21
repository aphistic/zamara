#include <string.h>
#include <iostream>

#include "zamara/mpq/mpq_file.h"
#include "zamara/mpq/mpq_compression.h"
#include "zamara/exception/zamara_exception.h"

using zamara::exception::ZamaraException;

namespace zamara {
  namespace mpq {
    
MpqFile::MpqFile(std::ifstream* archive, uint32_t archive_offset) {
  file_data_ = 0;
  is_open_ = false;

  archive_ = archive;
  archive_offset_ = archive_offset;
}

MpqFile::~MpqFile() {
  delete [] file_data_;
}

void MpqFile::Load(std::string filename, MpqHashEntry* hash_entry,
                   MpqBlockEntry* block_entry) {
  filename_ = filename;
  hash_entry_ = hash_entry;
  block_entry_ = block_entry;
}

void MpqFile::OpenFile() {
  delete [] file_data_;

  char* in_data = new char[block_entry_->compressed_size()];
  file_data_ = new char[block_entry_->file_size()];

  archive_->seekg(archive_offset_ + block_entry_->file_position(), std::ios::beg);
  archive_->read(in_data, block_entry_->compressed_size());

  if ((block_entry_->flags() & MPQ_FILE_COMPRESS) == MPQ_FILE_COMPRESS) {
    if ((*in_data & MPQ_COMPRESS_BZ2) == MPQ_COMPRESS_BZ2) { 
      MpqCompression::DecompressBzip2(in_data, block_entry_->compressed_size(),
                                      file_data_, block_entry_->file_size());
    }
    else if ((*in_data & MPQ_COMPRESS_NONE) == MPQ_COMPRESS_NONE) {
      // No file compression
      memcpy(file_data_, in_data, block_entry_->file_size());
    }
    else {
      // Uknown file compression
      throw ZamaraException("Unknown file compression found.",
                            ZamaraException::UNKNOWN_COMPRESSION);
    }
  }

  is_open_ = true;

  delete [] in_data;
}

bool MpqFile::IsOpen() {
  return is_open_;
}

char* MpqFile::FileData() {
  return file_data_;
}

void MpqFile::CloseFile() {
  delete [] file_data_;
  file_data_ = 0;

  is_open_ = false; 
}

std::string MpqFile::filename() {
  return filename_;
}

uint32_t MpqFile::file_size() {
  return block_entry_->file_size();
}

MpqHashEntry* MpqFile::hash_entry() {
  return hash_entry_;
}

MpqBlockEntry* MpqFile::block_entry() {
  return block_entry_;
}

  }
}
