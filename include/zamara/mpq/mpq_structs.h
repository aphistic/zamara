#ifndef ZAMARA_MPQ_MPQ_STRUCTS_H_
#define ZAMARA_MPQ_MPQ_STRUCTS_H_

#include <stdint.h>

struct MpqUserDataHeader
{
	uint32_t maxUserDataSize;
	uint32_t archiveOffset;
	uint32_t userDataSize;
};

struct MpqHeader
{
	uint32_t headerSize;
	uint32_t archiveSize;
	uint32_t formatVersion;

	uint8_t sectorSizeShift;

	uint32_t hashTableOffset;
	uint32_t blockTableOffset;
	uint32_t hashTableEntries;
	uint32_t blockTableEntries;

	uint64_t extendedBlockTableOffset;
	uint16_t hashTableOffsetHigh;
	uint16_t blockTableOffsetHigh;
};

#endif // ZAMARA_MPQ_MPQ_STRUCTS_H_
