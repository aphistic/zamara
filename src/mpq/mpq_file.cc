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
