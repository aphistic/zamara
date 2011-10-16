#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/endian/endian.h"

using namespace zamara::endian;

TEST(Endianness, CheckEndianness)
{
    uint32_t endianCheck = 16909060; // 0x01020304 on little endian
    if (endianCheck == 0x01020304)
    {
        ASSERT_FALSE(Endian::IsBigEndian());
    }
    else
    {
        ASSERT_TRUE(Endian::IsBigEndian());
    }
}
