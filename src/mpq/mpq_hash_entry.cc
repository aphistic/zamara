#include "zamara/mpq/mpq_hash_entry.h"
#include "zamara/endian/endian.h"

using zamara::endian::Endian;

namespace zamara {
  namespace mpq {

MpqHashEntry::MpqHashEntry() {
  
} 

MpqHashEntry::~MpqHashEntry() {
  
}

void MpqHashEntry::Load(char* buffer) {
  file_path_hash_a_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer)));

  file_path_hash_b_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 4)));

  language_ = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 8)));

  platform_ = Endian::LeToH16(
      *(reinterpret_cast<uint16_t*>(buffer + 10)));

  block_index_ = Endian::LeToH32(
      *(reinterpret_cast<uint32_t*>(buffer + 12)));
}

void MpqHashEntry::set_file_path_hash_a(uint32_t hash) {
  file_path_hash_a_ = hash;
}

uint32_t MpqHashEntry::file_path_hash_a() {
  return file_path_hash_a_;
}

void MpqHashEntry::set_file_path_hash_b(uint32_t hash) {
  file_path_hash_b_ = hash;
}

uint32_t MpqHashEntry::file_path_hash_b()
{
  return file_path_hash_b_;
}

void MpqHashEntry::set_language(uint16_t language)
{
  language_ = language;
}

uint16_t MpqHashEntry::language() {
  return language_;
}

void MpqHashEntry::set_platform(uint16_t platform)
{
  platform_ = platform;
}

uint16_t MpqHashEntry::platform() {
  return platform_;
}

void MpqHashEntry::set_block_index(uint32_t block_index) {
  block_index_ = block_index;
}

uint32_t MpqHashEntry::block_index() {
  return block_index_;
}

  }
}