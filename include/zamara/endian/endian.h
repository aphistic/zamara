#ifndef ZAMARA_ENDIAN_ENDIAN_H_
#define ZAMARA_ENDIAN_ENDIAN_H_

#include <stdint.h>

namespace zamara {
	namespace endian {

class Endian {
 public:
	static bool IsBigEndian();

	static uint16_t Swap16(uint16_t);
	static uint32_t Swap32(uint32_t);
	static uint64_t Swap64(uint64_t);

	static uint16_t LeToH16(uint16_t);
	static uint32_t LeToH32(uint32_t);
	static uint64_t LeToH64(uint64_t);
};

	}
}

#endif // ZAMARA_ENDIAN_ENDIAN_H_
