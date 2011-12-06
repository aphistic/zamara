#include "zamara/sc2/player.h"

namespace zamara {
  namespace sc2 {

void Player::Load(SerializedValue player_data) {
  name_ = player_data[0].AsString();
  id_ = player_data[1][3].AsInt64();
  race_ = player_data[2].AsString();
  color_.A = player_data[3][0].AsInt64();
  color_.R = player_data[3][1].AsInt64();
  color_.G = player_data[3][2].AsInt64();
  color_.B = player_data[3][3].AsInt64();
  team_ = player_data[5].AsInt64();
  handicap_ = player_data[6].AsInt64();
  outcome_ = player_data[8].AsInt64();
}

std::string Player::name() {
  return name_;
}

uint32_t Player::id() {
  return id_;
}

std::string Player::race() {
  return race_;
}

Color Player::color() {
  return color_;
}

uint8_t Player::team() {
  return team_;
}

uint32_t Player::handicap() {
  return handicap_;
}

uint8_t Player::outcome() {
  return outcome_;
}

  }
}