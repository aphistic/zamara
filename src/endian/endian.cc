#include "config.h"
#include "zamara/endian/endian.h"

namespace zamara {
  namespace endian {

bool Endian::IsBigEndian() {
  union {
    uint32_t i;
    char c[4];
  } testint = { 0x01020304 };

  return testint.c[0] == 1;
}

uint16_t Endian::Swap16(uint16_t val) {
  return  (val >> 8) | (val << 8);
}

uint32_t Endian::Swap32(uint32_t val) {
  return  (val >> 24) |
          ((val << 8) & 0x00ff0000) |
          ((val >> 8) & 0x0000ff00) |
          (val << 24);
}

uint64_t Endian::Swap64(uint64_t val) {
  return  (val >> 56) |
          ((val << 40)  & 0x00ff000000000000) |
          ((val << 24)  & 0x0000ff0000000000) |
          ((val << 8)   & 0x000000ff00000000) |
          ((val >> 8)   & 0x00000000ff000000) |
          ((val >> 24)  & 0x0000000000ff0000) |
          ((val >> 40)  & 0x000000000000ff00) |
          (val << 56);
}

uint16_t Endian::LeToH16(uint16_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap16(val);
}

uint32_t Endian::LeToH32(uint32_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap32(val);
}

uint64_t Endian::LeToH64(uint64_t val) {
  if (!IsBigEndian()) {
    return val;
  }
  return Swap64(val);
}

  }
}
