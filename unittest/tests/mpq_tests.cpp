#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/exception/zamara_exception.h"

using namespace zamara::mpq;
using namespace zamara::exception;

TEST(MpqFiles, MpqOpenFileFail)
{
	Mpq testMpq;
	ASSERT_THROW(testMpq.Load("files/DoesNotExist.SC2Replay"),
			ZamaraException);
	ASSERT_FALSE(testMpq.IsLoaded());
}

TEST(MpqFiles, MpqOpenFileSucceed)
{
	Mpq testMpq;
	testMpq.Load("files/replay1.SC2Replay");

	ASSERT_TRUE(testMpq.IsLoaded());
}
