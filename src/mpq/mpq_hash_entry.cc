/* Zamara Library
 * Copyright (c) 2011, Erik Davidson
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 
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