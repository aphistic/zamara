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
#include "zamara/endian/endian.h"

using namespace zamara::endian;

TEST(Endianness, CheckEndianness)
{
  // Use CMake to double check the endian check
  if (IS_BIG_ENDIAN)
  {
    ASSERT_TRUE(Endian::IsBigEndian());
  }
  else
  {
    ASSERT_FALSE(Endian::IsBigEndian());
  }
}

TEST(Endianness, Swap16Bit)
{
  ASSERT_EQ(0x0201, Endian::Swap16(0x0102));
}

TEST(Endianness, Swap32Bit)
{
  ASSERT_EQ(0x04030201, Endian::Swap32(0x01020304));
}

TEST(Endianness, Swap64Bit)
{
  ASSERT_EQ(0x0807060504030201, Endian::Swap64(0x0102030405060708));
}
