#include "zamara/sc2/replay.h"

#include "zamara/mpq/mpq_file.h"
#include "zamara/sc2/serialized_value.h"

using zamara::mpq::MpqFile;

namespace zamara {
  namespace sc2 {

Replay::Replay() {
}

Replay::~Replay() {
  players_.clear();
}

void Replay::Load(std::string file_path) {
  players_.clear();

  mpq_.Load(file_path);

  LoadDetails();
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
}

void Replay::LoadAttributes() {
  
}

  }
}
