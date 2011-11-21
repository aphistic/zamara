#ifndef ZAMARA_MPQ_MPQ_FILE_H_
#define ZAMARA_MPQ_MPQ_FILE_H_

#include <fstream>
#include <string>

#include "zamara/mpq/mpq_hash_entry.h"
#include "zamara/mpq/mpq_block_entry.h"

namespace zamara {
  namespace mpq {
    
class MpqFile {
 public:
  ~MpqFile();

  void Load(std::string filename, MpqHashEntry* hash_entry,
            MpqBlockEntry* block_entry);
  
  void OpenFile();
  bool IsOpen();
  char* FileData();
  void CloseFile();

  std::string filename();
  uint32_t file_size();
  MpqHashEntry* hash_entry();
  MpqBlockEntry* block_entry();

 private:
  friend class Mpq;

  MpqFile(std::ifstream* archive, uint32_t archive_offset);

  std::ifstream* archive_;
  uint32_t archive_offset_;

  std::string filename_;

  MpqHashEntry* hash_entry_;
  MpqBlockEntry* block_entry_;

  bool is_open_;
  char* file_data_;
};

  }
}

#endif // ZAMARA_MPQ_MPQ_FILE_H_
