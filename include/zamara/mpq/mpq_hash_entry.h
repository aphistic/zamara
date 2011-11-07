#ifndef ZAMARA_MPQ_MPQ_HASH_ENTRY_H_
#define ZAMARA_MPQ_MPQ_HASH_ENTRY_H_

#include <stdint.h>

namespace zamara {
  namespace mpq {

class MpqHashEntry {
 public:
  MpqHashEntry();
  ~MpqHashEntry();

  void Load(char* buffer);

  void set_file_path_hash_a(uint32_t hash);
  uint32_t file_path_hash_a();

  void set_file_path_hash_b(uint32_t hash);
  uint32_t file_path_hash_b();

  void set_language(uint16_t language);
  uint16_t language();

  void set_platform(uint16_t platform);
  uint16_t platform();

  void set_block_index(uint32_t block_index);
  uint32_t block_index();

 private:
  uint32_t file_path_hash_a_;
  uint32_t file_path_hash_b_;

  uint16_t language_;

  uint16_t platform_;

  uint32_t block_index_;
};


  }
}

#endif // ZAMARA_MPQ_MPQ_HASH_ENTRY_H_