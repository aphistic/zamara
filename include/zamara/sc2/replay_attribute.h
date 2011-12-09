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
