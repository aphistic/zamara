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

#ifndef ZAMARA_MPQ_MPQ_HASH_ENTRY_H_
#define ZAMARA_MPQ_MPQ_HASH_ENTRY_H_

#include <stdint.h>

namespace zamara {
  namespace mpq {

class MpqHashEntry {
 public:
  MpqHashEntry();
  ~MpqHashEntry();

  void Load(char* buffer);

  void set_file_path_hash_a(uint32_t hash);
  uint32_t file_path_hash_a();

  void set_file_path_hash_b(uint32_t hash);
  uint32_t file_path_hash_b();

  void set_language(uint16_t language);
  uint16_t language();

  void set_platform(uint16_t platform);
  uint16_t platform();

  void set_block_index(uint32_t block_index);
  uint32_t block_index();

 private:
  uint32_t file_path_hash_a_;
  uint32_t file_path_hash_b_;

  uint16_t language_;

  uint16_t platform_;

  uint32_t block_index_;
};


  }
}

#endif // ZAMARA_MPQ_MPQ_HASH_ENTRY_H_