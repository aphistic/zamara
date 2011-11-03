#ifndef ZAMARA_ENDIAN_ENDIAN_H_
#define ZAMARA_ENDIAN_ENDIAN_H_

#include <stdint.h>

namespace zamara
{
	namespace endian
	{

class Endian
{
public:
	static bool isBigEndian();

	static uint16_t swap16(uint16_t);
	static uint32_t swap32(uint32_t);
	static uint64_t swap64(uint64_t);

	static uint16_t leToH16(uint16_t);
	static uint32_t leToH32(uint32_t);
	static uint64_t leToH64(uint64_t);

};

	}
}

#endif // ZAMARA_ENDIAN_ENDIAN_H_
