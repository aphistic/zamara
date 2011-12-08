#include "config_test.h"

#include "gtest/gtest.h"

#include "zamara/sc2/replay.h"

using namespace std;
using namespace zamara::sc2;

TEST(Sc2Replay, LoadReplay)
{
  Replay replay;
  replay.Load(TR_1);

  // Replay Details
  ASSERT_STREQ("Discord IV", replay.map_name().c_str());
  ASSERT_EQ(1280548614, replay.timestamp());
  ASSERT_EQ(-14400, replay.timezone_offset());
  ASSERT_EQ(TYPE_2V2, replay.type());
  ASSERT_EQ(SPEED_FASTER, replay.speed());
  ASSERT_EQ(CATEGORY_LADDER, replay.category());

  // Players
  ASSERT_EQ(4, replay.players().size());

  // First Player
  ASSERT_STREQ("TehPartE", replay.players()[0]->name().c_str());
  ASSERT_EQ(PLAYER_HUMAN, replay.players()[0]->type());
  ASSERT_EQ(RACE_PROTOSS, replay.players()[0]->chosen_race());
  ASSERT_EQ(RACE_PROTOSS, replay.players()[0]->actual_race());
  ASSERT_EQ(DIFFICULTY_MEDIUM, replay.players()[0]->difficulty());
  ASSERT_EQ(COLOR_RED, replay.players()[0]->named_color());
  ASSERT_EQ(255, replay.players()[0]->color().A);
  ASSERT_EQ(180, replay.players()[0]->color().R);
  ASSERT_EQ(20, replay.players()[0]->color().G);
  ASSERT_EQ(30, replay.players()[0]->color().B);
  ASSERT_EQ(0, replay.players()[0]->team());
  ASSERT_EQ(100, replay.players()[0]->handicap());
  ASSERT_EQ(0, replay.players()[0]->outcome());

  // Second Player
  ASSERT_STREQ("totsgerber", replay.players()[1]->name().c_str());
  ASSERT_EQ(PLAYER_HUMAN, replay.players()[1]->type());
  ASSERT_EQ(RACE_ZERG, replay.players()[1]->chosen_race());
  ASSERT_EQ(RACE_ZERG, replay.players()[1]->actual_race());
  ASSERT_EQ(DIFFICULTY_MEDIUM, replay.players()[1]->difficulty());
  ASSERT_EQ(COLOR_BLUE, replay.players()[1]->named_color());
  ASSERT_EQ(255, replay.players()[1]->color().A);
  ASSERT_EQ(0, replay.players()[1]->color().R);
  ASSERT_EQ(66, replay.players()[1]->color().G);
  ASSERT_EQ(255, replay.players()[1]->color().B);
  ASSERT_EQ(1, replay.players()[1]->team());
  ASSERT_EQ(100, replay.players()[1]->handicap());
  ASSERT_EQ(0, replay.players()[1]->outcome());

  // Third Player
  ASSERT_STREQ("David", replay.players()[2]->name().c_str());
  ASSERT_EQ(PLAYER_HUMAN, replay.players()[2]->type());
  ASSERT_EQ(RACE_TERRAN, replay.players()[2]->chosen_race());
  ASSERT_EQ(RACE_TERRAN, replay.players()[2]->actual_race());
  ASSERT_EQ(DIFFICULTY_MEDIUM, replay.players()[2]->difficulty());
  ASSERT_EQ(COLOR_TEAL, replay.players()[2]->named_color());
  ASSERT_EQ(255, replay.players()[2]->color().A);
  ASSERT_EQ(28, replay.players()[2]->color().R);
  ASSERT_EQ(167, replay.players()[2]->color().G);
  ASSERT_EQ(234, replay.players()[2]->color().B);
  ASSERT_EQ(1, replay.players()[2]->team());
  ASSERT_EQ(100, replay.players()[2]->handicap());
  ASSERT_EQ(0, replay.players()[2]->outcome());

  // Fourth Player
  ASSERT_STREQ("Steven", replay.players()[3]->name().c_str());
  ASSERT_EQ(PLAYER_HUMAN, replay.players()[3]->type());
  ASSERT_EQ(RACE_TERRAN, replay.players()[3]->chosen_race());
  ASSERT_EQ(RACE_TERRAN, replay.players()[3]->actual_race());
  ASSERT_EQ(DIFFICULTY_MEDIUM, replay.players()[3]->difficulty());
  ASSERT_EQ(COLOR_PURPLE, replay.players()[3]->named_color());
  ASSERT_EQ(255, replay.players()[3]->color().A);
  ASSERT_EQ(84, replay.players()[3]->color().R);
  ASSERT_EQ(0, replay.players()[3]->color().G);
  ASSERT_EQ(129, replay.players()[3]->color().B);
  ASSERT_EQ(0, replay.players()[3]->team());
  ASSERT_EQ(100, replay.players()[3]->handicap());
  ASSERT_EQ(0, replay.players()[3]->outcome());
}
