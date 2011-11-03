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
TEST(MpqFiles, UserDataHeader)
{
	Mpq testMpq;
	testMpq.Load(TR_1);

	ASSERT_TRUE(testMpq.HasUserData());
	ASSERT_EQ(512, testMpq.user_data()->header().max_user_data_size);
	ASSERT_EQ(1024, testMpq.user_data()->header().archive_offset);
	ASSERT_EQ(60, testMpq.user_data()->header().user_data_size);
}

TEST(MpqFiles, ReadHeaderSize)
{
	Mpq testMpq;
	testMpq.Load(TR_1);

	ASSERT_EQ(44, testMpq.header().header_size);
}

TEST(MpqFiles, ReadArchiveSize)
{
	Mpq testMpq;
	testMpq.Load(TR_1);

	ASSERT_EQ(109012, testMpq.header().archive_size);
}
