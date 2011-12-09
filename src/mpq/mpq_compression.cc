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
 
#include <bzlib.h>
#include <iostream>

#include "zamara/mpq/mpq_compression.h"

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

  while ((result = BZ2_bzDecompress(&strm)) != BZ_STREAM_END) {
  }

  result = strm.total_out_lo32;

  BZ2_bzDecompressEnd(&strm);

  return result;
}

  }
}
