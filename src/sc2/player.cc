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
 
#include "zamara/sc2/player.h"

namespace zamara {
  namespace sc2 {

Player::Player() {
  named_color_ = COLOR_UNKNOWN;
  type_ = PLAYER_UNKNOWN;
  difficulty_ = DIFFICULTY_UNKNOWN;
  actual_race_ = RACE_UNKNOWN;
  chosen_race_ = RACE_UNKNOWN;
}

void Player::Load(SerializedValue player_data) {
  name_ = player_data[0].AsString();
  id_ = player_data[1][3].AsInt64();
  color_.A = player_data[3][0].AsInt64();
  color_.R = player_data[3][1].AsInt64();
  color_.G = player_data[3][2].AsInt64();
  color_.B = player_data[3][3].AsInt64();
  team_ = player_data[5].AsInt64();
  handicap_ = player_data[6].AsInt64();
  outcome_ = player_data[8].AsInt64();

  std::string race = player_data[2].AsString();
  if (race == "Protoss") {
    actual_race_ = RACE_PROTOSS;
  } else if (race == "Terran") {
    actual_race_ = RACE_TERRAN;
  } else if (race == "Zerg") {
    actual_race_ = RACE_ZERG;
  }
}

std::string Player::name() {
  return name_;
}

uint32_t Player::id() {
  return id_;
}

PlayerRace Player::chosen_race() {
  return chosen_race_;
}

void Player::set_chosen_race(PlayerRace race) {
  chosen_race_ = race;
}

PlayerRace Player::actual_race() {
  return actual_race_;
}

Color Player::color() {
  return color_;
}

PlayerColor Player::named_color() {
  return named_color_;
}

void Player::set_named_color(PlayerColor color) {
  named_color_ = color;
}

uint8_t Player::team() {
  return team_;
}

int Player::handicap() {
  return handicap_;
}

void Player::set_handicap(int handicap) {
  handicap_ = handicap;
}

uint8_t Player::outcome() {
  return outcome_;
}

PlayerType Player::type() {
  return type_;
}

void Player::set_type(PlayerType player_type) {
  type_ = player_type;
}

PlayerDifficulty Player::difficulty() {
  return difficulty_;
}

void Player::set_difficulty(PlayerDifficulty difficulty) {
  difficulty_ = difficulty;
}

  }
}
