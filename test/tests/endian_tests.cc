#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/endian/endian.h"

using namespace zamara::endian;

TEST(Endianness, CheckEndianness)
{
	// Use CMake to double check the endian check
	if (IS_BIG_ENDIAN)
	{
		ASSERT_TRUE(Endian::isBigEndian());
	}
	else
	{
		ASSERT_FALSE(Endian::isBigEndian());
	}
}

TEST(Endianness, Swap16Bit)
{
	ASSERT_EQ(0x0201, Endian::swap16(0x0102));
}

TEST(Endianness, Swap32Bit)
{
	ASSERT_EQ(0x04030201, Endian::swap32(0x01020304));
}

TEST(Endianness, Swap64Bit)
{
	ASSERT_EQ(0x0807060504030201, Endian::swap64(0x0102030405060708));
}
