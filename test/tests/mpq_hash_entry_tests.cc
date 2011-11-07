#include "gtest/gtest.h"

#include "zamara/mpq/mpq_hash_entry.h"

using namespace zamara::mpq;

TEST(MpqHashEntry, LoadEntry) {
  uint32_t decrypted_table[] = {
    0xD38437CB, 0x07DFEAEC, 0x00000000, 0x00000009
  };

  MpqHashEntry entry;

  entry.Load(reinterpret_cast<char*>(decrypted_table));

  ASSERT_EQ(0xD38437CB, entry.file_path_hash_a());
  ASSERT_EQ(0x07DFEAEC, entry.file_path_hash_b());
  ASSERT_EQ(0x0000, entry.language());
  ASSERT_EQ(0x0000, entry.platform());
  ASSERT_EQ(0x00000009, entry.block_index());
}