#ifndef ZAMARA_SC2_REPLAY_H_
#define ZAMARA_SC2_REPLAY_H_

#include <vector>

#include "boost/tr1/memory.hpp"

#include "zamara/mpq/mpq.h"
#include "zamara/sc2/player.h"

using zamara::mpq::Mpq;

namespace zamara {
  namespace sc2 {

enum GameType {
  TYPE_UNKNOWN,
  TYPE_1V1,
  TYPE_2V2,
  TYPE_3V3,
  TYPE_4V4,
  TYPE_FFA,
  TYPE_6V6,
  TYPE_CUSTOM
};

enum GameSpeed {
  SPEED_UNKNOWN,
  SPEED_SLOWER,
  SPEED_SLOW,
  SPEED_NORMAL,
  SPEED_FAST,
  SPEED_FASTER
};

enum GameCategory {
  CATEGORY_UNKNOWN,
  CATEGORY_PRIVATE,
  CATEGORY_LADDER,
  CATEGORY_PUBLIC
};

class Replay {
 public:
  Replay();
  ~Replay();

  void Load(std::string file_path);

  std::vector<std::tr1::shared_ptr<Player> > players();
  std::string map_name();
  uint64_t timestamp();
  int64_t timezone_offset();

  GameType type();
  void set_type(GameType type);

  GameSpeed speed();
  void set_speed(GameSpeed speed);

  GameCategory category();
  void set_category(GameCategory category);

 private:
  void LoadDetails();
  void LoadAttributes();

  void LoadPlayerAttribute(ReplayAttribute attr);
  void LoadGlobalAttribute(ReplayAttribute attr);

  std::string file_path_;
  Mpq mpq_;
  std::vector<std::tr1::shared_ptr<Player> > players_;

  std::string map_name_;
  uint64_t timestamp_;
  int64_t timezone_offset_;

  GameType type_;
  GameSpeed speed_;
  GameCategory category_;
};

  }
}

#endif // ZAMARA_SC2_REPLAY_H_
