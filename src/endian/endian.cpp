#include "config.h"
#include "zamara/endian/endian.h"

namespace zamara
{
	namespace endian
	{

bool Endian::IsBigEndian()
{
	union {
		uint32_t i;
		char c[4];
	} testint = { 0x01020304 };

	return testint.c[0] == 1;
}

uint16_t Endian::Swap16(uint16_t val)
{
}

uint32_t Endian::Swap32(uint32_t val)
{
}

uint64_t Endian::Swap64(uint64_t val)
{
}

uint16_t Endian::LeToH16(uint16_t val)
{
	if (!IsBigEndian())
	{
		return val;
	}
	return Swap16(val);
}

uint32_t Endian::LeToH32(uint32_t val)
{
	if (!IsBigEndian())
	{
		return val;
	}
	return Swap32(val);
}

uint64_t Endian::LeToH64(uint64_t val)
{
	if (!IsBigEndian())
	{
		return val;
	}
	return Swap64(val);
}

	}
}
