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

enum MpqCompressFlag {
  MPQ_COMPRESS_NONE   = 0x00,
  MPQ_COMPRESS_BZ2    = 0x10
};

  }
}

#endif // ZAMARA_MPQ_MPQ_COMPRESSION_H_
