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

#ifndef ZAMARA_MPQ_MPQ_FILE_H_
#define ZAMARA_MPQ_MPQ_FILE_H_

#include <fstream>
#include <string>

#include "zamara/mpq/mpq_hash_entry.h"
#include "zamara/mpq/mpq_block_entry.h"

namespace zamara {
  namespace mpq {
    
class MpqFile {
 public:
  ~MpqFile();

  void Load(std::string filename, MpqHashEntry* hash_entry,
            MpqBlockEntry* block_entry);
  
  void OpenFile();
  bool IsOpen();
  char* FileData();
  void CloseFile();

  std::string filename();
  uint32_t file_size();
  MpqHashEntry* hash_entry();
  MpqBlockEntry* block_entry();

 private:
  friend class Mpq;

  MpqFile(std::ifstream* archive, uint32_t archive_offset);

  std::ifstream* archive_;
  uint32_t archive_offset_;

  std::string filename_;

  MpqHashEntry* hash_entry_;
  MpqBlockEntry* block_entry_;

  bool is_open_;
  char* file_data_;
};

  }
}

#endif // ZAMARA_MPQ_MPQ_FILE_H_
