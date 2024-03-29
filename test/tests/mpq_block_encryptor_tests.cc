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
 
#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq_block_encryptor.h"

using namespace zamara::mpq;

TEST(MpqFileBlockEncryption, HashString)
{
  MpqBlockEncryptor enc("this is a string", 0x100, 0, 0);
  ASSERT_EQ(450484832, enc.HashString());

  enc.set_offset(0x200);
  ASSERT_EQ(2082422408, enc.HashString());
}

TEST(MpqFileBlockEncryption, EncryptionTable)
{
  MpqBlockEncryptor enc("this is a string", 0x100, 0, 0);

  ASSERT_EQ(1439053538u, enc.encryption_table()[0]);
  ASSERT_EQ(2690928833u, enc.encryption_table()[100]);
  ASSERT_EQ(2859196621u, enc.encryption_table()[1000]);
  ASSERT_EQ(1929586796u, enc.encryption_table()[1279]);
}

TEST(MpqFileBlockEncryption, DecryptHashTable)
{
  uint32_t hash_table[] = {
    0x55B8F807, 0x3C8EB44F, 0xAC7BA87C, 0xE0001AAE, // Hash Entry 1
    0xC5DCC9C7, 0xC3FE6C3E, 0xA73302A2, 0xB76D1BB8  // Hash Entry 2
  };

  MpqBlockEncryptor enc("(hash table)", 0x300, hash_table, 32);
  enc.Decrypt();

  ASSERT_EQ(0xD38437CB, hash_table[0]);
  ASSERT_EQ(0x07DFEAEC, hash_table[1]);
  ASSERT_EQ(0x00000000, hash_table[2]);
  ASSERT_EQ(0x00000009, hash_table[3]);

  ASSERT_EQ(0xAAC2A54B, hash_table[4]);
  ASSERT_EQ(0xF4762B95, hash_table[5]);
  ASSERT_EQ(0x00000000, hash_table[6]);
  ASSERT_EQ(0x00000002, hash_table[7]);
}

TEST(MpqFileBlockEncryption, DecryptBlockTable)
{
  uint32_t block_table[] = {
    0x3D4867A7, 0xCA08D1FC, 0xF835BCE1, 0xE933F197, // Block Entry 1
    0xB3B35213, 0x10C07F07, 0x0DD8F894, 0xD3A41ED6  // Block Entry 2
  };

  MpqBlockEncryptor enc("(block table)", 0x300, block_table, 32);
  enc.Decrypt();

  ASSERT_EQ(0x0000002C, block_table[0]);
  ASSERT_EQ(0x00000251, block_table[1]);
  ASSERT_EQ(0x00000251, block_table[2]);
  ASSERT_EQ(0x81000200, block_table[3]);

  ASSERT_EQ(0x0000027D, block_table[4]);
  ASSERT_EQ(0x000002A0, block_table[5]);
  ASSERT_EQ(0x00000482, block_table[6]);
  ASSERT_EQ(0x81000200, block_table[7]);
}