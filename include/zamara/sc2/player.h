#ifndef ZAMARA_SC2_PLAYER_H_
#define ZAMARA_SC2_PLAYER_H_

#include <stdint.h>
#include <string>

#include "zamara/zamara.h"

#include "zamara/sc2/serialized_value.h"

namespace zamara {
  namespace sc2 {

class Player {
 public:
  void Load(SerializedValue player_data);

  std::string name();
  uint32_t id();
  std::string race();
  Color color();
  uint8_t team();
  uint32_t handicap();
  uint8_t outcome();

 private:
  std::string name_;
  uint32_t id_;
  std::string race_;
  Color color_;
  uint8_t team_;
  uint32_t handicap_;
  uint8_t outcome_;
};
    
  }
}

#endif // ZAMARA_SC2_PLAYER_H_