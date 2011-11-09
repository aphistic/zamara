#ifndef ZAMARA_MPQ_MPQ_COMPRESSION_H_
#define ZAMARA_MPQ_MPQ_COMPRESSION_H_

#include <stdint.h>

namespace zamara {
  namespace mpq {
    
class MpqCompression {
 public:
  static int32_t DecompressBzip2(char* in_buf, uint32_t in_size,
                                 char* out_buf, uint32_t out_size);

};

  }
}

#endif // ZAMARA_MPQ_MPQ_COMPRESSION_H_