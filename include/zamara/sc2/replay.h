#ifndef ZAMARA_SC2_REPLAY_H_
#define ZAMARA_SC2_REPLAY_H_

#include <vector>

#include "boost/tr1/memory.hpp"

#include "zamara/mpq/mpq.h"
#include "zamara/sc2/player.h"

using zamara::mpq::Mpq;

namespace zamara {
  namespace sc2 {

class Replay {
 public:
  Replay();
  ~Replay();

  void Load(std::string file_path);

  std::vector<std::tr1::shared_ptr<Player> > players();
  std::string map_name();
  uint64_t timestamp();
  int64_t timezone_offset();

 private:
  void LoadDetails();
  void LoadAttributes();

  std::string file_path_;
  Mpq mpq_;
  std::vector<std::tr1::shared_ptr<Player> > players_;

  std::string map_name_;
  uint64_t timestamp_;
  int64_t timezone_offset_;
};

  }
}

#endif // ZAMARA_SC2_REPLAY_H_
