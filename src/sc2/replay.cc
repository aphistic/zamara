#include <stdlib.h>

#include "zamara/sc2/replay.h"

#include "zamara/mpq/mpq_file.h"
#include "zamara/sc2/serialized_value.h"
#include "zamara/sc2/replay_attribute.h"

using zamara::mpq::MpqFile;

namespace zamara {
  namespace sc2 {

Replay::Replay() {
}

Replay::~Replay() {
  players_.clear();
  mpq_.Close();
}

void Replay::Load(std::string file_path) {
  players_.clear();

  mpq_.Load(file_path);

  LoadDetails();
  LoadAttributes();
}

std::vector<std::tr1::shared_ptr<Player> > Replay::players() {
  return players_;
}

std::string Replay::map_name() {
  return map_name_;
}

uint64_t Replay::timestamp() {
  return timestamp_;
}

int64_t Replay::timezone_offset() {
  return timezone_offset_;
}

GameType Replay::type() {
  return type_;
}

void Replay::set_type(GameType type) {
  type_ = type;
}

GameSpeed Replay::speed() {
  return speed_;
}

void Replay::set_speed(GameSpeed speed) {
  speed_ = speed;
}

GameCategory Replay::category() {
  return category_;
}

void Replay::set_category(GameCategory category) {
  category_ = category;
}

void Replay::LoadDetails() {
  MpqFile details_file = mpq_.GetFile("replay.details");

  details_file.OpenFile();
  SerializedValue details;
  details.Load(details_file.FileData());

  for (size_t idx = 0; idx < details[0].size(); idx++)
  {
    std::tr1::shared_ptr<Player> player(new Player());
    player->Load(details[0][idx]);
    players_.push_back(player);
  }

  map_name_ = details[1].AsString();

  timezone_offset_ = (int64_t) details[6].AsInt64();
  timezone_offset_ = timezone_offset_ / 10000000;

  // Load timestamp and convert it to unix time
  timestamp_ = (uint64_t) details[5].AsInt64();
  timestamp_ = (timestamp_ - 116444735995904000) / 10000000;

  details_file.CloseFile();
}

void Replay::LoadAttributes() {
  MpqFile file = mpq_.GetFile("replay.attributes.events");
  file.OpenFile();

  AttributesFile attr_file;
  attr_file.Load(file.FileData());

  size_t attr_count = attr_file.count();
  for (uint32_t idx = 0; idx < attr_count; idx++) {
    if (attr_file[idx].IsPlayer()) {
      LoadPlayerAttribute(attr_file[idx]);
    } else {
      LoadGlobalAttribute(attr_file[idx]);
    }
  }
}

void Replay::LoadPlayerAttribute(ReplayAttribute attr) {
  uint8_t player_id = attr.player_id() - 1;

  switch (attr.id()) {
    case 0x01F4:
      if (attr.str_value() == "Humn") {
        players_[player_id]->set_type(PLAYER_HUMAN);
      } else if (attr.str_value() == "Comp") {
        players_[player_id]->set_type(PLAYER_COMPUTER);
      }
      break;
    case 0x0BB9:
      if (attr.str_value() == "RAND") {
        players_[player_id]->set_chosen_race(RACE_RANDOM);
      } else if (attr.str_value() == "Terr") {
        players_[player_id]->set_chosen_race(RACE_TERRAN);
      } else if (attr.str_value() == "Prot") {
        players_[player_id]->set_chosen_race(RACE_PROTOSS);
      } else if (attr.str_value() == "Zerg") {
        players_[player_id]->set_chosen_race(RACE_ZERG);
      }
      break;
    case 0x0BBC:
      if (attr.str_value() == "VyEy") {
        players_[player_id]->set_difficulty(DIFFICULTY_VERY_EASY);
      } else if (attr.str_value() == "Easy") {
        players_[player_id]->set_difficulty(DIFFICULTY_EASY);
      } else if (attr.str_value() == "Medi") {
        players_[player_id]->set_difficulty(DIFFICULTY_MEDIUM);
      } else if (attr.str_value() == "Hard") {
        players_[player_id]->set_difficulty(DIFFICULTY_HARD);
      } else if (attr.str_value() == "VyHd") {
        players_[player_id]->set_difficulty(DIFFICULTY_VERY_HARD);
      } else if (attr.str_value() == "Insa") {
        players_[player_id]->set_difficulty(DIFFICULTY_INSANE);
      }
      break;
    case 0x0BBB:
      players_[player_id]->set_handicap(atoi(attr.str_value().c_str()));
      break;
    case 0x0BBA:
      if (attr.str_value() == "tc01") {
        players_[player_id]->set_named_color(COLOR_RED);
      } else if (attr.str_value() == "tc02") {
        players_[player_id]->set_named_color(COLOR_BLUE);
      } else if (attr.str_value() == "tc03") {
        players_[player_id]->set_named_color(COLOR_TEAL);
      } else if (attr.str_value() == "tc04") {
        players_[player_id]->set_named_color(COLOR_PURPLE);
      } else if (attr.str_value() == "tc05") {
        players_[player_id]->set_named_color(COLOR_YELLOW);
      } else if (attr.str_value() == "tc06") {
        players_[player_id]->set_named_color(COLOR_ORANGE);
      } else if (attr.str_value() == "tc07") {
        players_[player_id]->set_named_color(COLOR_GREEN);
      } else if (attr.str_value() == "tc08") {
        players_[player_id]->set_named_color(COLOR_LIGHT_PINK);
      } else if (attr.str_value() == "tc09") {
        players_[player_id]->set_named_color(COLOR_VIOLET);
      } else if (attr.str_value() == "tc10") {
        players_[player_id]->set_named_color(COLOR_LIGHT_GREY);
      } else if (attr.str_value() == "tc11") {
        players_[player_id]->set_named_color(COLOR_DARK_GREEN);
      } else if (attr.str_value() == "tc12") {
        players_[player_id]->set_named_color(COLOR_BROWN);
      } else if (attr.str_value() == "tc13") {
        players_[player_id]->set_named_color(COLOR_LIGHT_GREEN);
      } else if (attr.str_value() == "tc14") {
        players_[player_id]->set_named_color(COLOR_DARK_GREY);
      } else if (attr.str_value() == "tc15") {
        players_[player_id]->set_named_color(COLOR_PINK);
      }
      break;
  }
}

void Replay::LoadGlobalAttribute(ReplayAttribute attr) {
  switch (attr.id())
  {
    case 0x07D1:
      if (attr.str_value() == "1v1") {
        set_type(TYPE_1V1);
      } else if (attr.str_value() == "2v2") {
        set_type(TYPE_2V2);
      } else if (attr.str_value() == "3v3") {
        set_type(TYPE_3V3);
      } else if (attr.str_value() == "4v4") {
        set_type(TYPE_4V4);
      } else if (attr.str_value() == "FFA") {
        set_type(TYPE_FFA);
      } else if (attr.str_value() == "6v6") {
        set_type(TYPE_6V6);
      } else if (attr.str_value() == "Cust") {
        set_type(TYPE_CUSTOM);
      }
      break;
    case 0x0BB8:
      if (attr.str_value() == "Slor") {
        set_speed(SPEED_SLOWER);
      } else if (attr.str_value() == "Slow") {
        set_speed(SPEED_SLOW);
      } else if (attr.str_value() == "Norm") {
        set_speed(SPEED_NORMAL);
      } else if (attr.str_value() == "Fast") {
        set_speed(SPEED_FAST);
      } else if (attr.str_value() == "Fasr") {
        set_speed(SPEED_FASTER);
      }
      break;
    case 0x0BC1:
      if (attr.str_value() == "Priv") {
        set_category(CATEGORY_PRIVATE);
      } else if (attr.str_value() == "Amm") {
        set_category(CATEGORY_LADDER);
      } else if (attr.str_value() == "Pub") {
        set_category(CATEGORY_PUBLIC);
      }
      break;
  } 
}

  }
}
