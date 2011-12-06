#include <stdexcept>

#include "zamara/endian/endian.h"
#include "zamara/sc2/replay_attribute.h"

using zamara::endian::Endian;

namespace zamara {
  namespace sc2 {

// ReplayAttribute class defs 
size_t ReplayAttribute::Load(char* data) {
  header_ = *(reinterpret_cast<uint32_t*>(data));
  id_ = *(reinterpret_cast<uint32_t*>(data + 4));
  player_id_ = *(reinterpret_cast<uint8_t*>(data + 8));
  value_ = *(reinterpret_cast<uint32_t*>(data + 9));

  uint32_t temp_value = Endian::Swap32(value_);
  char* str_data = reinterpret_cast<char*>(&temp_value);
  uint8_t offset = -1;
  while (str_data[++offset] == 0x00);
  str_value_ = std::string(str_data + offset, sizeof(temp_value) - offset);

  return 13; // At this point each attribute is always 13 bytes
}

uint32_t ReplayAttribute::header() {
  return header_;
}

uint32_t ReplayAttribute::id() {
  return id_;
}

uint8_t ReplayAttribute::player_id() {
  return player_id_;
}

uint32_t ReplayAttribute::value() {
  return value_;
}

std::string ReplayAttribute::str_value() {
  return str_value_;
}

// AttributesFile class defs
AttributesFile::~AttributesFile() {
  attributes_.clear();
}

void AttributesFile::Load(char* data) {
  uint32_t offset = -1;
  while (data[++offset] == 0x00);

  size_t count = *(reinterpret_cast<uint32_t*>(data + offset));
  offset += 4;

  for (size_t idx = 0; idx < count; idx++) {
    std::tr1::shared_ptr<ReplayAttribute> attr(new ReplayAttribute());
    offset += attr->Load(data + offset);

    attributes_.push_back(attr);
  }
}

ReplayAttribute AttributesFile::operator[] (size_t key) {
  if (key < 0 || key >= attributes_.size()) {
    throw std::out_of_range("Supplied index is out of range.");
  }

  return *(attributes_[key]);
}

size_t AttributesFile::count() {
  return attributes_.size();
}

  }
}
