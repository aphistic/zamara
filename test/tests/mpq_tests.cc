#include <string>

#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/exception/zamara_exception.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::exception;

TEST(MpqFiles, OpenFileFail)
{
  Mpq testMpq;
  try {
    testMpq.Load(TR_NOT_EXIST);
  } catch (ZamaraException& ex) {
    ASSERT_EQ(ZamaraException::FILE_NOT_FOUND, ex.exception_type());
  }
  ASSERT_FALSE(testMpq.IsLoaded());
}

TEST(MpqFiles, OpenFileSucceed)
{
  Mpq testMpq;
  testMpq.Load(TR_1);
    
  ASSERT_TRUE(testMpq.IsLoaded());
}

TEST(MpqFiles, OpenFileNotMpq)
{
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

  ASSERT_TRUE(testMpq.HasUserData());
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
