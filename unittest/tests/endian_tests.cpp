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
