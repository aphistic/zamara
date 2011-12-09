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
 
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>

#include "zamara/exception/zamara_exception.h"
#include "zamara/sc2/serialized_value.h"

using zamara::exception::ZamaraException;

namespace zamara {
  namespace sc2 {
    
SerializedValue::SerializedValue() {
  
}

SerializedValue::~SerializedValue() {
  members_.clear();
  keys_.clear();
}

void SerializedValue::Load(char* data) {
  LoadData(data);
}

bool SerializedValue::IsString() {
  return type() == STRING;
}

bool SerializedValue::IsArray() {
  return type() == ARRAY;
}

bool SerializedValue::IsKeyValue() {
  return type() == KEY_VALUE;
}

bool SerializedValue::IsInt8() {
  return type() == INT8;
}

bool SerializedValue::IsInt32() {
  return type() == INT32;
}

bool SerializedValue::IsInt64() {
  return type() == INT_VLF;
}

std::string SerializedValue::AsString() {
  return string_value_;
}

int8_t SerializedValue::AsInt8() {
  return (int8_t) int_value_;
}

int32_t SerializedValue::AsInt32() {
  return (int32_t) int_value_;
}

int64_t SerializedValue::AsInt64() {
  return (int64_t) int_value_;
}

SerializedValue SerializedValue::operator[] (size_t key) {
  if (key < 0 || key >= members_.size()) {
    throw std::out_of_range("Supplied index is out of range.");
  }

  std::tr1::shared_ptr<SerializedValue> val = members_[key];
  return *val;
}

std::vector<std::tr1::shared_ptr<SerializedValue> > SerializedValue::members() {
  return members_;
}

std::vector<int8_t> SerializedValue::keys() {
  return keys_;
}

SerializedValue::ValueType SerializedValue::type() {
  return type_;
}

size_t SerializedValue::size() {
  switch (type()) {
    case ARRAY:
    case KEY_VALUE:
      return members_.size();
    default:
      throw ZamaraException("bad",
                            ZamaraException::FILE_NOT_FOUND);
  }
}

size_t SerializedValue::LoadData(char* data) {
  members_.clear();
  keys_.clear();

  size_t size_loaded = 0;

  switch (*data) {
    case STRING:
      size_loaded += LoadString(data + 1);
      break;
    case ARRAY:
      size_loaded += LoadArray(data + 1);
      break;
    case KEY_VALUE:
      size_loaded += LoadKeyValue(data + 1);
      break;
    case INT8:
      size_loaded += LoadInt8(data + 1);
      break;
    case INT32:
      size_loaded += LoadInt32(data + 1);
      break;
    case INT_VLF:
      size_loaded += LoadIntVlf(data + 1);
      break;
    default:
      throw ZamaraException("Unknown serialization type.",
                            ZamaraException::UNKNOWN_SERIALIZATION);
      break;
  }
  size_loaded++; // Add one for the data type byte that's skipped

  return size_loaded;
}

size_t SerializedValue::LoadString(char* data) {
  type_ = STRING;

  int64_t length;
  size_t amount_read = ReadIntVlf(data, &length);
  string_value_ = std::string(data + amount_read, length);
  
  return length + 1; 
}

size_t SerializedValue::LoadArray(char* data) {
  type_ = ARRAY;

  size_t offset = 2; // An array starts with 0x01 0x00 that can be skipped
  int64_t elements;
  offset += ReadIntVlf(data + offset, &elements);

  for (char idx = 0; idx < elements; idx++) {
    std::tr1::shared_ptr<SerializedValue> new_value(new SerializedValue());
    offset += new_value->LoadData(data + offset);
    members_.push_back(new_value);
  }
  return offset;
}

size_t SerializedValue::LoadKeyValue(char* data) {
  type_ = KEY_VALUE;

  int64_t elements;
  size_t offset = ReadIntVlf(data, &elements);

  for (char idx = 0; idx < elements; idx++) {
    keys_.push_back(*(data + offset));
    offset++;

    std::tr1::shared_ptr<SerializedValue> new_value(new SerializedValue());
    offset += new_value->LoadData(data + offset);
    members_.push_back(new_value);
  }
  return offset;
}

size_t SerializedValue::LoadInt8(char* data) {
  type_ = INT8;
  int_value_ = (*data) >> 1;
  return 1;
}

size_t SerializedValue::LoadInt32(char* data) {
  type_ = INT32;
  int_value_ = (*reinterpret_cast<int32_t*>(data)) >> 1;
  return 4;
}

size_t SerializedValue::LoadIntVlf(char* data) {
  type_ = INT_VLF;
  size_t amount_read = ReadIntVlf(data, &int_value_);
  return amount_read;
}

size_t SerializedValue::ReadIntVlf(char* data, int64_t* result) {
  unsigned char current_byte;
  int32_t byte_count = 0;
  int64_t value = 0;

  do {
    current_byte = *(data + byte_count);
    value += (int64_t) (current_byte & 0x7F) << (7 * byte_count);
    byte_count++;
  } while ((current_byte & 0x80) > 0);

  *result = (value & 1) ? -(value >> 1) : (value >> 1);

  return byte_count;
}

  }
}
