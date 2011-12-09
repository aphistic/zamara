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

#ifndef ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
#define ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_

#include <string>
#include <stdint.h>

namespace zamara {
	namespace mpq {

class MpqBlockEncryptor {
 public:
 	MpqBlockEncryptor();
	MpqBlockEncryptor(std::string key, uint16_t offset,
										uint32_t* buffer, size_t size);
	~MpqBlockEncryptor();

	static uint32_t HashString(std::string key, uint16_t offset);

	uint32_t HashString();
	void Decrypt();
	void Encrypt();

	void set_key(std::string key);
	std::string key();
	
	void set_offset(uint16_t offset);
	uint16_t offset();

	void set_buffer(uint32_t* buffer);
	uint32_t* buffer();

	void set_size(size_t size);
	size_t size();

	uint32_t* encryption_table();

 private:
 	void GenerateEncryptionTable();

 	uint32_t* encryption_table_;
	std::string key_;
	uint16_t offset_;
	uint32_t* buffer_;
	size_t size_;
};

	}
}

#endif // ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
