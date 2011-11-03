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
        	testMpq.load(TR_NOT_EXIST);
	} catch (ZamaraException& ex) {
		ASSERT_EQ(ZamaraException::FILE_NOT_FOUND, ex.getType());
	}
	ASSERT_FALSE(testMpq.isLoaded());
}

TEST(MpqFiles, OpenFileSucceed)
{
	Mpq testMpq;
	testMpq.load(TR_1);
    
	ASSERT_TRUE(testMpq.isLoaded());
}

TEST(MpqFiles, OpenFileNotMpq)
{
	Mpq testMpq;
	try {
		testMpq.load(TR_NOT_MPQ);
	} catch (ZamaraException& ex) {
		ASSERT_EQ(ZamaraException::FILE_NOT_MPQ, ex.getType());
	}
	ASSERT_FALSE(testMpq.isLoaded());			
}

// User Data Tets
TEST(MpqFiles, UserDataHeader)
{
	Mpq testMpq;
	testMpq.load(TR_1);

	ASSERT_TRUE(testMpq.hasUserData());
	ASSERT_EQ(512, testMpq.getUserData()->header.maxUserDataSize);
	ASSERT_EQ(1024, testMpq.getUserData()->header.archiveOffset);
	ASSERT_EQ(60, testMpq.getUserData()->header.userDataSize);
}

TEST(MpqFiles, ReadHeaderSize)
{
	Mpq testMpq;
	testMpq.load(TR_1);

	ASSERT_EQ(44, testMpq.header.headerSize);
}

TEST(MpqFiles, ReadArchiveSize)
{
	Mpq testMpq;
	testMpq.load(TR_1);

	ASSERT_EQ(109012, testMpq.header.archiveSize);
}
