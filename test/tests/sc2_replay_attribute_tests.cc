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
 
#include <stdexcept>

#include "config_test.h"

#include "gtest/gtest.h"
#include "zamara/mpq/mpq.h"
#include "zamara/mpq/mpq_file.h"
#include "zamara/sc2/replay_attribute.h"

using namespace std;
using namespace zamara::mpq;
using namespace zamara::sc2;

TEST(Sc2Data, ReadAttributeOutOfRange) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  MpqFile file = testMpq.GetFile("replay.attributes.events");

  file.OpenFile();

  AttributesFile attr_file;
  attr_file.Load(file.FileData());
  
  ASSERT_EQ(80, attr_file.count());
  
  ASSERT_THROW(attr_file[-1], std::out_of_range);
  ASSERT_NO_THROW(attr_file[0]);
  ASSERT_NO_THROW(attr_file[79]);
  ASSERT_THROW(attr_file[80], std::out_of_range);  
}

TEST(Sc2Data, ReadAttributes) {
  Mpq testMpq;
  testMpq.Load(TR_1);

  MpqFile file = testMpq.GetFile("replay.attributes.events");

  file.OpenFile();

  AttributesFile attr_file;
  attr_file.Load(file.FileData());

  ASSERT_EQ(80, attr_file.count());

  ASSERT_EQ(0x000003E7, attr_file[0].header());
  ASSERT_EQ(0x0BBF, attr_file[0].id());
  ASSERT_EQ(0x01, attr_file[0].player_id());
  ASSERT_EQ(0x50617274, attr_file[0].value());

  ASSERT_EQ(0x000003E7, attr_file[4].header());
  ASSERT_EQ(0x01F4, attr_file[4].id());
  ASSERT_EQ(0x01, attr_file[4].player_id());
  ASSERT_EQ(0x48756D6E, attr_file[4].value());
  ASSERT_STREQ("Humn", attr_file[4].str_value().c_str());

  ASSERT_EQ(0x000003E7, attr_file[5].header());
  ASSERT_EQ(0x01F4, attr_file[5].id());
  ASSERT_EQ(0x02, attr_file[5].player_id());
  ASSERT_EQ(0x48756D6E, attr_file[5].value());
  ASSERT_STREQ("Humn", attr_file[5].str_value().c_str());

  ASSERT_EQ(0x000003E7, attr_file[8].header());
  ASSERT_EQ(0x0BB9, attr_file[8].id());
  ASSERT_EQ(0x01, attr_file[8].player_id());
  ASSERT_EQ(0x50726F74, attr_file[8].value());
  ASSERT_STREQ("Prot", attr_file[8].str_value().c_str()); 

  ASSERT_EQ(0x000003E7, attr_file[24].header());
  ASSERT_EQ(0x0BBB, attr_file[24].id());
  ASSERT_EQ(0x01, attr_file[24].player_id());
  ASSERT_EQ(0x20313030, attr_file[24].value());
  ASSERT_STREQ("100", attr_file[24].str_value().c_str());

  ASSERT_EQ(0x000003E7, attr_file[28].header());
  ASSERT_EQ(0x07D6, attr_file[28].id());
  ASSERT_EQ(0x01, attr_file[28].player_id());
  ASSERT_EQ(0x00005431, attr_file[28].value());
  ASSERT_STREQ("T1", attr_file[28].str_value().c_str());

  ASSERT_EQ(0x000003E7, attr_file[75].header());
  ASSERT_EQ(0x0BB8, attr_file[75].id());
  ASSERT_EQ(0x10, attr_file[75].player_id());
  ASSERT_EQ(0x46617372, attr_file[75].value());
  ASSERT_STREQ("Fasr", attr_file[75].str_value().c_str());
}
