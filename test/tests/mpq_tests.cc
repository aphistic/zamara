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
 
#include <string>

#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/sc2/serialized_value.h"
#include "zamara/exception/zamara_exception.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::sc2;
using namespace zamara::exception;

TEST(MpqFiles, OpenFileFail) {
  Mpq testMpq;
  try {
    testMpq.Load(TR_NOT_EXIST);
  } catch (ZamaraException& ex) {
    ASSERT_EQ(ZamaraException::FILE_NOT_FOUND, ex.exception_type());
  }
  ASSERT_FALSE(testMpq.IsLoaded());
}

TEST(MpqFiles, OpenFileSucceed) {
  Mpq testMpq;
  testMpq.Load(TR_1);
    
  ASSERT_TRUE(testMpq.IsLoaded());
}

TEST(MpqFiles, OpenFileNotMpq) {
  Mpq testMpq;
  try {
    testMpq.Load(TR_NOT_MPQ);
  } catch (ZamaraException& ex) {
    ASSERT_EQ(ZamaraException::FILE_NOT_MPQ, ex.exception_type());
  }
  ASSERT_FALSE(testMpq.IsLoaded());
}

// User Data Tets
TEST(MpqFiles, UserDataHeader) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  ASSERT_EQ(512, testMpq.user_data()->header().max_user_data_size);
  ASSERT_EQ(1024, testMpq.user_data()->header().archive_offset);
  ASSERT_EQ(60, testMpq.user_data()->header().user_data_size);
}

TEST(MpqFiles, ReadMpqHeader) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  ASSERT_EQ(44, testMpq.header().header_size);
  ASSERT_EQ(109012, testMpq.header().archive_size);
  ASSERT_EQ(0x01, testMpq.header().format_version);
  ASSERT_EQ(0x03, testMpq.header().block_size);
  ASSERT_EQ(108596, testMpq.header().hash_table_offset);
  ASSERT_EQ(108852, testMpq.header().block_table_offset);
  ASSERT_EQ(16, testMpq.header().hash_table_entries);
  ASSERT_EQ(10, testMpq.header().block_table_entries);
  ASSERT_EQ(0, testMpq.header().extended_block_table_offset);
  ASSERT_EQ(0, testMpq.header().hash_table_offset_high);
  ASSERT_EQ(0, testMpq.header().block_table_offset_high);
}

TEST(MpqFiles, ReadFiles) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  ASSERT_STREQ("replay.attributes.events",
               testMpq.files()[0].filename().c_str());
  ASSERT_STREQ("replay.details",
               testMpq.files()[1].filename().c_str());
  ASSERT_STREQ("replay.game.events",
               testMpq.files()[2].filename().c_str());
  ASSERT_STREQ("replay.initData",
               testMpq.files()[3].filename().c_str());
  ASSERT_STREQ("replay.load.info",
               testMpq.files()[4].filename().c_str());
  ASSERT_STREQ("replay.message.events",
               testMpq.files()[5].filename().c_str());
  ASSERT_STREQ("replay.smartcam.events",
               testMpq.files()[6].filename().c_str());
  ASSERT_STREQ("replay.sync.events",
               testMpq.files()[7].filename().c_str());
}

TEST(MpqFiles, GetFileByName) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  ASSERT_THROW(testMpq.GetFile("replay.does.not.exist"), ZamaraException);
  try {
    testMpq.GetFile("replay.does.not.exist");
  } catch (ZamaraException& ex) {
    ASSERT_EQ(ZamaraException::MPQ_FILE_NOT_FOUND, ex.exception_type());
  }

  MpqFile file = testMpq.GetFile("replay.details");
  ASSERT_STREQ("replay.details", file.filename().c_str());
}