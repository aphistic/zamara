#ifndef ZAMARA_SC2_REPLAY_ATTRIBUTE_H_
#define ZAMARA_SC2_REPLAY_ATTRIBUTE_H_

#include <vector>
#include <string>

#include <stdint.h>
#include <stddef.h>

#include "boost/tr1/memory.hpp"

namespace zamara {
  namespace sc2 {
   
class ReplayAttribute {
 public:
  size_t Load(char* data);

  bool IsGlobal();
  bool IsPlayer();

  uint32_t header();
  uint32_t id();
  uint8_t player_id();
  uint32_t value();
  std::string str_value();

 private:
  uint32_t header_;
  uint32_t id_;
  uint8_t player_id_;
  uint32_t value_;
  std::string str_value_;
};

class AttributesFile {
 public:
  ~AttributesFile();
  
  void Load(char* data);

  ReplayAttribute operator[] (uint32_t key);

  size_t count();

 private:
  std::vector<std::tr1::shared_ptr<ReplayAttribute> > attributes_;
};


  }
}

#endif // ZAMARA_SC2_REPLAY_ATTRIBUTE_H_
