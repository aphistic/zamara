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
 
#include "gtest/gtest.h"

#include "zamara/endian/endian.h"
#include "zamara/mpq/mpq_hash_entry.h"

using namespace zamara::mpq;
using zamara::endian::Endian;

TEST(MpqHashEntry, LoadEntry) {
  uint32_t decrypted_table[] = {
    Endian::LeToH32(0xD38437CB),
    Endian::LeToH32(0x07DFEAEC),
    Endian::LeToH32(0x00000000),
    Endian::LeToH32(0x00000009)
  };

  MpqHashEntry entry;

  entry.Load(reinterpret_cast<char*>(decrypted_table));

  ASSERT_EQ(0xD38437CB, entry.file_path_hash_a());
  ASSERT_EQ(0x07DFEAEC, entry.file_path_hash_b());
  ASSERT_EQ(0x0000, entry.language());
  ASSERT_EQ(0x0000, entry.platform());
  ASSERT_EQ(0x00000009, entry.block_index());
}