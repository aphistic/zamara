#ifndef ZAMARA_MPQ_MPQ_STRUCTS_H_
#define ZAMARA_MPQ_MPQ_STRUCTS_H_

#include <stdint.h>

struct MpqUserDataHeader {
	uint32_t max_user_data_size;
	uint32_t archive_offset;
	uint32_t user_data_size;
};

struct MpqHeader {
	uint32_t header_size;
	uint32_t archive_size;
	uint32_t format_version;

	uint8_t sector_size_shift;

	uint32_t hash_table_offset;
	uint32_t block_table_offset;
	uint32_t hash_table_entries;
	uint32_t block_table_entries;

	uint64_t extended_block_table_offset;
	uint16_t hash_table_offset_high;
	uint16_t block_table_offset_high;
};

#endif // ZAMARA_MPQ_MPQ_STRUCTS_H_
