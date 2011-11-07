#ifndef ZAMARA_MPQ_MPQ_FILE_H_
#define ZAMARA_MPQ_MPQ_FILE_H_

#include <string>

namespace zamara {
  namespace mpq {
    
class MpqFile {
 public:
  MpqFile();
  ~MpqFile();

 private:
  std::string filename;
  
};

  }
}

#endif // ZAMARA_MPQ_MPQ_FILE_H_