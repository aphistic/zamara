#include "zamara/endian/endian.h"
#include "zamara/mpq/mpq_block_entry.h"

using zamara::endian::Endian;

namespace zamara {
  namespace mpq {
    
MpqBlockEntry::MpqBlockEntry() {
  
}

MpqBlockEntry::~MpqBlockEntry() {
  
}

void MpqBlockEntry::Load(char* buffer) {
  file_position_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer)));

  compressed_size_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 4)));

  file_size_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 8)));

  flags_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 12)));
}

void MpqBlockEntry::set_file_position(uint32_t file_position) {
  file_position_ = file_position;
}

uint32_t MpqBlockEntry::file_position() {
  return file_position_;
}

void MpqBlockEntry::set_compressed_size(uint32_t compressed_size) {
  compressed_size_ = compressed_size;
}

uint32_t MpqBlockEntry::compressed_size() {
  return compressed_size_;
}

void MpqBlockEntry::set_file_size(uint32_t file_size) {
  file_size_ = file_size;
}

uint32_t MpqBlockEntry::file_size() {
  return file_size_;
}

void MpqBlockEntry::set_flags(uint32_t flags) {
  flags_ = flags;
}

uint32_t MpqBlockEntry::flags() {
  return flags_;
}

  }
}