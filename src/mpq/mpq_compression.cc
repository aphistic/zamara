#include "zamara/mpq/mpq_compression.h"

#include <bzlib.h>

namespace zamara {
  namespace mpq {
    
int32_t MpqCompression::DecompressBzip2(char* in_buf, uint32_t in_size,
                                        char* out_buf, uint32_t out_size) {
  int32_t result = 0;
  bz_stream strm;

  strm.bzalloc  = NULL;
  strm.bzfree   = NULL;

  if ((result = BZ2_bzDecompressInit(&strm, 0, 0)) != BZ_OK) {
    return result;
  }

  strm.next_in   = in_buf;
  strm.avail_in  = in_size;
  strm.next_out  = out_buf;
  strm.avail_out = out_size;

  while (BZ2_bzDecompress(&strm) != BZ_STREAM_END);

  result = strm.total_out_lo32;

  BZ2_bzDecompressEnd(&strm);

  return result;
}

  }
}