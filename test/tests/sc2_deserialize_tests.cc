#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/mpq/mpq_file.h"
#include "zamara/sc2/serialized_value.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::sc2;

TEST(Sc2Data, DeserializeReplayDetails) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  MpqFile file = testMpq.GetFile("replay.details");

  file.OpenFile();
  SerializedValue value;
  value.Load(file.FileData());

  // Root Node
  ASSERT_TRUE(value.IsKeyValue());

  // Player Array
  ASSERT_TRUE(value[0].IsArray());
  ASSERT_EQ(4, value[0].size());

  // First Player
  ASSERT_TRUE(value[0][0].IsKeyValue());
  ASSERT_TRUE(value[0][0][0].IsString());
  ASSERT_STREQ("TehPartE", value[0][0][0].AsString().c_str()); // Name
  ASSERT_TRUE(value[0][0][2].IsString());
  ASSERT_STREQ("Protoss", value[0][0][2].AsString().c_str()); // Race
  ASSERT_TRUE(value[0][0][3].IsKeyValue());
  ASSERT_TRUE(value[0][0][3][0].IsInt64());
  ASSERT_EQ(255, value[0][0][3][0].AsInt64()); // Color - A
  ASSERT_TRUE(value[0][0][3][1].IsInt64());
  ASSERT_EQ(180, value[0][0][3][1].AsInt64()); // Color - R
  ASSERT_TRUE(value[0][0][3][2].IsInt64());
  ASSERT_EQ(20, value[0][0][3][2].AsInt64()); // Color - G
  ASSERT_TRUE(value[0][0][3][3].IsInt64());
  ASSERT_EQ(30, value[0][0][3][3].AsInt64()); // Color - B
  ASSERT_TRUE(value[0][0][5].IsInt64());
  ASSERT_EQ(0, value[0][0][5].AsInt64()); // Team
  ASSERT_TRUE(value[0][0][6].IsInt64());
  ASSERT_EQ(100, value[0][0][6].AsInt64()); // Handicap
  ASSERT_TRUE(value[0][0][8].IsInt64());
  ASSERT_EQ(0, value[0][0][8].AsInt64()); // Outcome

  // Second Player
  ASSERT_TRUE(value[0][1].IsKeyValue());
  ASSERT_TRUE(value[0][1][0].IsString());
  ASSERT_STREQ("totsgerber", value[0][1][0].AsString().c_str()); // Name
  ASSERT_TRUE(value[0][1][2].IsString());
  ASSERT_STREQ("Zerg", value[0][1][2].AsString().c_str()); // Race
  ASSERT_TRUE(value[0][1][3].IsKeyValue());
  ASSERT_TRUE(value[0][1][3][0].IsInt64());
  ASSERT_EQ(255, value[0][1][3][0].AsInt64()); // Color - A
  ASSERT_TRUE(value[0][1][3][1].IsInt64());
  ASSERT_EQ(0, value[0][1][3][1].AsInt64()); // Color - R
  ASSERT_TRUE(value[0][1][3][2].IsInt64());
  ASSERT_EQ(66, value[0][1][3][2].AsInt64()); // Color - G
  ASSERT_TRUE(value[0][1][3][3].IsInt64());
  ASSERT_EQ(255, value[0][1][3][3].AsInt64()); // Color - B
  ASSERT_TRUE(value[0][1][5].IsInt64());
  ASSERT_EQ(1, value[0][1][5].AsInt64()); // Team
  ASSERT_TRUE(value[0][1][6].IsInt64());
  ASSERT_EQ(100, value[0][1][6].AsInt64()); // Handicap
  ASSERT_TRUE(value[0][1][8].IsInt64());
  ASSERT_EQ(0, value[0][1][8].AsInt64()); // Outcome

  // Third Player
  ASSERT_TRUE(value[0][2].IsKeyValue());
  ASSERT_TRUE(value[0][2][0].IsString());
  ASSERT_STREQ("David", value[0][2][0].AsString().c_str()); // Name
  ASSERT_TRUE(value[0][2][2].IsString());
  ASSERT_STREQ("Terran", value[0][2][2].AsString().c_str()); // Race
  ASSERT_TRUE(value[0][2][3].IsKeyValue());
  ASSERT_TRUE(value[0][2][3][0].IsInt64());
  ASSERT_EQ(255, value[0][2][3][0].AsInt64()); // Color - A
  ASSERT_TRUE(value[0][2][3][1].IsInt64());
  ASSERT_EQ(28, value[0][2][3][1].AsInt64()); // Color - R
  ASSERT_TRUE(value[0][2][3][2].IsInt64());
  ASSERT_EQ(167, value[0][2][3][2].AsInt64()); // Color - G
  ASSERT_TRUE(value[0][2][3][3].IsInt64());
  ASSERT_EQ(234, value[0][2][3][3].AsInt64()); // Color - B
  ASSERT_TRUE(value[0][2][5].IsInt64());
  ASSERT_EQ(1, value[0][2][5].AsInt64()); // Team
  ASSERT_TRUE(value[0][2][6].IsInt64());
  ASSERT_EQ(100, value[0][2][6].AsInt64()); // Handicap
  ASSERT_TRUE(value[0][2][8].IsInt64());
  ASSERT_EQ(0, value[0][2][8].AsInt64()); // Outcome

  // Fourth Player
  ASSERT_TRUE(value[0][3].IsKeyValue());
  ASSERT_TRUE(value[0][3][0].IsString());
  ASSERT_STREQ("Steven", value[0][3][0].AsString().c_str()); // Name
  ASSERT_TRUE(value[0][3][2].IsString());
  ASSERT_STREQ("Terran", value[0][3][2].AsString().c_str()); // Race
  ASSERT_TRUE(value[0][3][3].IsKeyValue());
  ASSERT_TRUE(value[0][3][3][0].IsInt64());
  ASSERT_EQ(255, value[0][3][3][0].AsInt64()); // Color - A
  ASSERT_TRUE(value[0][3][3][1].IsInt64());
  ASSERT_EQ(84, value[0][3][3][1].AsInt64()); // Color - R
  ASSERT_TRUE(value[0][3][3][2].IsInt64());
  ASSERT_EQ(0, value[0][3][3][2].AsInt64()); // Color - G
  ASSERT_TRUE(value[0][3][3][3].IsInt64());
  ASSERT_EQ(129, value[0][3][3][3].AsInt64()); // Color - B
  ASSERT_TRUE(value[0][3][5].IsInt64());
  ASSERT_EQ(0, value[0][3][5].AsInt64()); // Team
  ASSERT_TRUE(value[0][3][6].IsInt64());
  ASSERT_EQ(0, value[0][3][6].AsInt64()); // Handicap
  ASSERT_TRUE(value[0][3][8].IsInt64());
  ASSERT_EQ(0, value[0][3][8].AsInt64()); // Outcome

  // Map Name
  ASSERT_TRUE(value[1].IsString());
  ASSERT_STREQ("Discord IV", value[1].AsString().c_str());

  // Some Minimap Thing
  ASSERT_TRUE(value[3].IsKeyValue());
  ASSERT_TRUE(value[3][0].IsString());
  ASSERT_STREQ("Minimap.tga", value[3][0].AsString().c_str());

  // Datetime of game
  ASSERT_TRUE(value[5].IsInt64());
  ASSERT_EQ(18446744073372380903U, (uint64_t) value[5].AsInt64());

  // Timezone offset
  ASSERT_TRUE(value[6].IsInt64());
  ASSERT_EQ(18446744073590956000U, (uint64_t) value[6].AsInt64());
}