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
