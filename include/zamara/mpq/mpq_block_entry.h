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

#ifndef ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_
#define ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_

#include <stdint.h>

namespace zamara {
  namespace mpq {
    
class MpqBlockEntry {
 public:
  MpqBlockEntry();
  ~MpqBlockEntry();
  
  void Load(char* buffer);
  
  void set_file_position(uint32_t file_position);
  uint32_t file_position();

  void set_compressed_size(uint32_t compressed_size);
  uint32_t compressed_size();

  void set_file_size(uint32_t file_size);
  uint32_t file_size();

  void set_flags(uint32_t flags);
  uint32_t flags();

 private:
  uint32_t file_position_;
  uint32_t compressed_size_;
  uint32_t file_size_;
  uint32_t flags_;  
};

enum MpqFileFlag {
  MPQ_FILE_IMPLODE       = 0x00000100,
  MPQ_FILE_COMPRESS      = 0x00000200,
  MPQ_FILE_ENCRYPTED     = 0x00010000,
  MPQ_FILE_FIX_KEY       = 0x00020000,
  MPQ_FILE_PATCH_FILE    = 0x00100000,
  MPQ_FILE_SINGLE_UNIT   = 0x01000000,
  MPQ_FILE_DELETE_MARKER = 0x02000000,
  MPQ_FILE_SECTOR_CRC    = 0x04000000,
  MPQ_FILE_EXISTS        = 0x80000000
};

  }
}

#endif // ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_
