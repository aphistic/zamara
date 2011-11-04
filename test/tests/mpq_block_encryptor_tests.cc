#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq_block_encryptor.h"

using namespace zamara::mpq;

TEST(MpqFileBlockEncryption, HashString)
{
  MpqBlockEncryptor enc("this is a string", 0x100, 0, 0);
  ASSERT_EQ(450484832, enc.HashString());

  enc.set_offset(0x200);
  ASSERT_EQ(2082422408, enc.HashString());
}

TEST(MpqFileBlockEncryption, EncryptionTable)
{
  MpqBlockEncryptor enc("this is a string", 0x100, 0, 0);

  ASSERT_EQ(1439053538u, enc.encryption_table()[0]);
  ASSERT_EQ(2690928833u, enc.encryption_table()[100]);
  ASSERT_EQ(2859196621u, enc.encryption_table()[1000]);
  ASSERT_EQ(1929586796u, enc.encryption_table()[1279]);
}
