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
 
#include <algorithm>
#include <iostream>

#include "zamara/mpq/mpq_block_encryptor.h"

namespace zamara {
	namespace mpq {

MpqBlockEncryptor::MpqBlockEncryptor(std::string key, uint16_t offset,
                                     uint32_t* buffer, size_t size) {
  key_ = key;
  offset_ = offset;
  buffer_ = buffer;
  size_ = size;

  encryption_table_ = 0;

  GenerateEncryptionTable();
}

MpqBlockEncryptor::~MpqBlockEncryptor() {
  delete [] encryption_table_;
}

uint32_t MpqBlockEncryptor::HashString(std::string key,
                                              uint16_t offset) {
  MpqBlockEncryptor encryptor(key, offset, 0, 0);
  uint32_t result = encryptor.HashString();

  return result;
}

uint32_t MpqBlockEncryptor::HashString() {
  uint32_t seed1 = 0x7FED7FED;
  uint32_t seed2 = 0xEEEEEEEE;

  std::string ucase(key_.length(), '\0');
  std::transform(key_.begin(), key_.end(), ucase.begin(), ::toupper);

  for (uint32_t idx = 0; idx < ucase.length(); idx++)
  {
    char current_char = ucase[idx];
    uint32_t value = encryption_table()[offset_ + current_char];
    seed1 = (value ^ (seed1 + seed2)) & 0xFFFFFFFF;
    seed2 = (current_char + seed1 + seed2 + (seed2 << 5) + 3) & 0xFFFFFFFF;
  }

  return seed1;
}

void MpqBlockEncryptor::Decrypt() {
  uint32_t seed1 = HashString();
  uint32_t seed2 = 0xEEEEEEEE;
  std::string reasult = "";
  size_t size = size_;

  uint32_t ch;
  for (; size >= 4; size -= 4) {
    seed2 += encryption_table()[0x400 + (seed1 & 0xFF)];
    seed2 &= 0xFFFFFFFF;
    ch = *(reinterpret_cast<uint32_t*>(buffer_)) ^ (seed1 + seed2);
    seed1 = ((~seed1 << 0x15) + 0x11111111) | (seed1 >> 0x0B);
    seed2 = ch + seed2 + (seed2 << 5) + 3;

    *buffer_++ = ch;
  }
}

void MpqBlockEncryptor::Encrypt() {
  
}

void MpqBlockEncryptor::set_key(std::string key) {
  key_ = key;
}

std::string MpqBlockEncryptor::key() {
  return key_;
}

void MpqBlockEncryptor::set_offset(uint16_t offset) {
  offset_ = offset;
}

uint16_t MpqBlockEncryptor::offset() {
  return offset_;
}

void MpqBlockEncryptor::set_buffer(uint32_t* buffer) {
  buffer_ = buffer;
}

uint32_t* MpqBlockEncryptor::buffer() {
  return buffer_;
}

void MpqBlockEncryptor::set_size(size_t size) {
  size_ = size;
}

size_t MpqBlockEncryptor::size() {
  return size_;
}

uint32_t* MpqBlockEncryptor::encryption_table() {
  return encryption_table_;
}

void MpqBlockEncryptor::GenerateEncryptionTable() {
  // Free the memory if the table already exists
  delete [] encryption_table_;
  encryption_table_ = new uint32_t[1280];

  uint32_t seed = 0x00100001;

  for (int main_idx = 0; main_idx < 256; main_idx++) {
    uint32_t current_idx = main_idx;

    for (int inner_idx = 0; inner_idx < 5; inner_idx++) {
      seed = (seed * 125 + 3) % 0x2AAAAB;
      uint32_t temp1 = (seed & 0xFFFF) << 0x10;

      seed = (seed * 125 + 3) % 0x2AAAAB;
      uint32_t temp2 = (seed & 0xFFFF);

      encryption_table_[current_idx] = (temp1 | temp2);

      current_idx += 0x100;
    }
  }
}

	}
}
