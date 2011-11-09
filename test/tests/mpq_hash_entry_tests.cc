#include "gtest/gtest.h"

#include "zamara/endian/endian.h"
#include "zamara/mpq/mpq_hash_entry.h"

using namespace zamara::mpq;
using zamara::endian::Endian;

TEST(MpqHashEntry, LoadEntry) {
  uint32_t decrypted_table[] = {
    Endian::LeToH32(0xD38437CB),
    Endian::LeToH32(0x07DFEAEC),
    Endian::LeToH32(0x00000000),
    Endian::LeToH32(0x00000009)
  };

  MpqHashEntry entry;

  entry.Load(reinterpret_cast<char*>(decrypted_table));

  ASSERT_EQ(0xD38437CB, entry.file_path_hash_a());
  ASSERT_EQ(0x07DFEAEC, entry.file_path_hash_b());
  ASSERT_EQ(0x0000, entry.language());
  ASSERT_EQ(0x0000, entry.platform());
  ASSERT_EQ(0x00000009, entry.block_index());
}