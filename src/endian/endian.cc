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
 
#include "config.h"
#include "zamara/endian/endian.h"

namespace zamara {
  namespace endian {

bool Endian::IsBigEndian() {
  union {
    uint32_t i;
    char c[4];
  } testint = { 0x01020304 };

  return testint.c[0] == 1;
}

uint16_t Endian::Swap16(uint16_t val) {
  return  (val >> 8) | (val << 8);
}

uint32_t Endian::Swap32(uint32_t val) {
  return  (val >> 24) |
          ((val << 8) & 0x00ff0000) |
          ((val >> 8) & 0x0000ff00) |
          (val << 24);
}

uint64_t Endian::Swap64(uint64_t val) {
  return  (val >> 56) |
          ((val << 40)  & 0x00ff000000000000) |
          ((val << 24)  & 0x0000ff0000000000) |
          ((val << 8)   & 0x000000ff00000000) |
          ((val >> 8)   & 0x00000000ff000000) |
          ((val >> 24)  & 0x0000000000ff0000) |
          ((val >> 40)  & 0x000000000000ff00) |
          (val << 56);
}

uint16_t Endian::LeToH16(uint16_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap16(val);
}

uint32_t Endian::LeToH32(uint32_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap32(val);
}

uint64_t Endian::LeToH64(uint64_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap64(val);
}

  }
}
