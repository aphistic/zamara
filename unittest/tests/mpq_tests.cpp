#include <string>

#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/exception/zamara_exception.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::exception;

TEST(MpqFiles, MpqOpenFileFail)
{
	string testFile = string(TEST_DIR); testFile.append("/files/does_not_exist.SC2Replay");

	Mpq testMpq;
	try {
        	testMpq.Load(testFile.c_str());
	} catch (ZamaraException& ex) {
		ASSERT_EQ(ZamaraException::FILE_NOT_FOUND, ex.getType());
	}
	ASSERT_FALSE(testMpq.IsLoaded());
}

TEST(MpqFiles, MpqOpenFileSucceed)
{
	string testFile = string(TEST_DIR); testFile.append("/files/replay1.SC2Replay");
    
	Mpq testMpq;
	testMpq.Load(testFile.c_str());
    
	ASSERT_TRUE(testMpq.IsLoaded());
}

TEST(MpqFiles, MpqOpenFileNotMpq)
{
	string testFile = string(TEST_DIR); testFile.append("/files/not_a_replay.SC2Replay");

	Mpq testMpq;
	try {
		testMpq.Load(testFile.c_str());
	} catch (ZamaraException& ex) {
		ASSERT_EQ(ZamaraException::FILE_NOT_MPQ, ex.getType());
	}
	ASSERT_FALSE(testMpq.IsLoaded());			
}
