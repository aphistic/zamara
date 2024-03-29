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

#ifndef ZAMARA_SC2_PLAYER_H_
#define ZAMARA_SC2_PLAYER_H_

#include <stdint.h>
#include <string>

#include "zamara/zamara.h"

#include "zamara/sc2/serialized_value.h"
#include "zamara/sc2/replay_attribute.h"

namespace zamara {
  namespace sc2 {

enum PlayerType {
  PLAYER_UNKNOWN,
  PLAYER_HUMAN,
  PLAYER_COMPUTER
};

enum PlayerDifficulty {
  DIFFICULTY_UNKNOWN,
  DIFFICULTY_VERY_EASY,
  DIFFICULTY_EASY,
  DIFFICULTY_MEDIUM,
  DIFFICULTY_HARD,
  DIFFICULTY_VERY_HARD,
  DIFFICULTY_INSANE
};

enum PlayerRace {
  RACE_UNKNOWN,
  RACE_RANDOM,
  RACE_TERRAN,
  RACE_PROTOSS,
  RACE_ZERG
};

enum PlayerColor {
  COLOR_UNKNOWN,
  COLOR_RED,
  COLOR_BLUE,
  COLOR_TEAL,
  COLOR_PURPLE,
  COLOR_YELLOW,
  COLOR_ORANGE,
  COLOR_GREEN,
  COLOR_LIGHT_PINK,
  COLOR_VIOLET,
  COLOR_LIGHT_GREY,
  COLOR_DARK_GREEN,
  COLOR_BROWN,
  COLOR_LIGHT_GREEN,
  COLOR_DARK_GREY,
  COLOR_PINK
};

class Player {
 public:
  Player();

  void Load(SerializedValue player_data);

  std::string name();
  uint32_t id();
  Color color();
  PlayerColor named_color();
  void set_named_color(PlayerColor color);
  uint8_t team();
  int handicap();
  void set_handicap(int handicap);
  uint8_t outcome();

  PlayerType type();
  void set_type(PlayerType player_type);

  PlayerDifficulty difficulty();
  void set_difficulty(PlayerDifficulty difficulty);

  PlayerRace actual_race();
  void set_actual_race(PlayerRace race);

  PlayerRace chosen_race();
  void set_chosen_race(PlayerRace race);

 private:
  std::string name_;
  uint32_t id_;
  Color color_;
  PlayerColor named_color_;
  uint8_t team_;
  int handicap_;
  uint8_t outcome_;

  PlayerType type_;
  PlayerDifficulty difficulty_;
  PlayerRace actual_race_;
  PlayerRace chosen_race_;
};
    
  }
}

#endif // ZAMARA_SC2_PLAYER_H_
