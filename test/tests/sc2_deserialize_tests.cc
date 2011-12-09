/* Zamara Library
 * Copyright (c) 2011, Erik Davidson
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 
#include <stdexcept>

#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/mpq/mpq_file.h"
#include "zamara/sc2/serialized_value.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::sc2;

TEST(Sc2Data, SerializedValueIndexOutOfRange) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  MpqFile file = testMpq.GetFile("replay.details");

  file.OpenFile();
  SerializedValue value;
  value.Load(file.FileData());

  // Make sure the [] operator throws an exception if the index is
  // below 0 or above the highest index

  ASSERT_THROW(value[-1], out_of_range);
  ASSERT_NO_THROW(value[0]);

  ASSERT_EQ(14, value.size());

  ASSERT_NO_THROW(value[13]);
  ASSERT_THROW(value[14], out_of_range);
}

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
  ASSERT_TRUE(value[0][0][1][3].IsInt64());
  ASSERT_EQ(278960, value[0][0][1][3].AsInt64());  // Player Id
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
  ASSERT_TRUE(value[0][1][1][3].IsInt64());
  ASSERT_EQ(297523, value[0][1][1][3].AsInt64()); // Player Id
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
  ASSERT_TRUE(value[0][2][1][3].IsInt64());
  ASSERT_EQ(549011, value[0][2][1][3].AsInt64()); // Player Id
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
  ASSERT_TRUE(value[0][3][1][3].IsInt64());
  ASSERT_EQ(752194, value[0][3][1][3].AsInt64()); // Player Id
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
  ASSERT_EQ(129250222145273475, (uint64_t) value[5].AsInt64());

  // Timezone offset
  ASSERT_TRUE(value[6].IsInt64());
  ASSERT_EQ(-144000000000, (int64_t) value[6].AsInt64());
}
