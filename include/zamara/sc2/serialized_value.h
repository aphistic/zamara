#ifndef ZAMARA_SC2_SERIALIZED_VALUE_H_
#define ZAMARA_SC2_SERIALIZED_VALUE_H_

#include <stdint.h>
#include <vector>

#include "boost/tr1/memory.hpp"

namespace zamara {
  namespace sc2 {

class SerializedValue {
 public:
  /**
   * The different types that SerializedValue
   * can represent.
   */
  enum ValueType {
    STRING    = 0x02,
    ARRAY     = 0x04,
    KEY_VALUE = 0x05,
    INT8      = 0x06,
    INT32     = 0x07,
    INT_VLF   = 0x09
  };

  SerializedValue();
  ~SerializedValue();

  void Load(char* data);

  bool IsString();
  bool IsArray();
  bool IsKeyValue();
  bool IsInt8();
  bool IsInt32();
  bool IsInt64();

  std::string AsString();
  int8_t AsInt8();
  int32_t AsInt32();
  int64_t AsInt64();

  /*
   * Operators
   */
  SerializedValue operator[] (size_t key);

  std::vector<std::tr1::shared_ptr<SerializedValue> > members();
  std::vector<int8_t> keys();
  SerializedValue::ValueType type();
  size_t size();

 private:
  std::vector<std::tr1::shared_ptr<SerializedValue> > members_;
  std::vector<int8_t> keys_;

  SerializedValue::ValueType type_;
  std::string string_value_;
  int64_t int_value_;

  size_t LoadData(char* data);
  size_t LoadString(char* data);
  size_t LoadArray(char* data);
  size_t LoadKeyValue(char* data);
  size_t LoadInt8(char* data);
  size_t LoadInt32(char* data);
  size_t LoadIntVlf(char* data);

  size_t ReadIntVlf(char* data, int64_t* result);
};
 
  }
}

#endif // ZAMARA_SC2_SERIALIZED_VALUE_H_
