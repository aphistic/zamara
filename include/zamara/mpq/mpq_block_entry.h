#ifndef ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_
#define ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_

#include <stdint.h>

namespace zamara {
  namespace mpq {
    
class MpqBlockEntry {
 public:
  MpqBlockEntry();
  ~MpqBlockEntry();
  
  void Load(char* buffer);
  
  void set_file_position(uint32_t file_position);
  uint32_t file_position();

  void set_compressed_size(uint32_t compressed_size);
  uint32_t compressed_size();

  void set_file_size(uint32_t file_size);
  uint32_t file_size();

  void set_flags(uint32_t flags);
  uint32_t flags();

 private:
  uint32_t file_position_;
  uint32_t compressed_size_;
  uint32_t file_size_;
  uint32_t flags_;  
};

enum MpqFileFlag {
  MPQ_FILE_IMPLODE       = 0x00000100,
  MPQ_FILE_COMPRESS      = 0x00000200,
  MPQ_FILE_ENCRYPTED     = 0x00010000,
  MPQ_FILE_FIX_KEY       = 0x00020000,
  MPQ_FILE_PATCH_FILE    = 0x00100000,
  MPQ_FILE_SINGLE_UNIT   = 0x01000000,
  MPQ_FILE_DELETE_MARKER = 0x02000000,
  MPQ_FILE_SECTOR_CRC    = 0x04000000,
  MPQ_FILE_EXISTS        = 0x80000000
};

  }
}

#endif // ZAMARA_MPQ_MPQ_BLOCK_ENTRY_H_
