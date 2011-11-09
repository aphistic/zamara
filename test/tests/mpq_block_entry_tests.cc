#include "gtest/gtest.h"

#include "zamara/endian/endian.h"
#include "zamara/mpq/mpq_block_entry.h"

using namespace zamara::mpq;
using zamara::endian::Endian;

TEST(MpqBlockEntry, LoadEntry) {
  uint32_t decrypted_table[] = {
    Endian::LeToH32(0x0000002C),
    Endian::LeToH32(0x00000251),
    Endian::LeToH32(0x00000251),
    Endian::LeToH32(0x81000200)
  };

  MpqBlockEntry entry;

  entry.Load(reinterpret_cast<char*>(decrypted_table));

  ASSERT_EQ(0x0000002C, entry.file_position());
  ASSERT_EQ(593, entry.compressed_size());
  ASSERT_EQ(593, entry.file_size());
  ASSERT_EQ(0x81000200, entry.flags());
}