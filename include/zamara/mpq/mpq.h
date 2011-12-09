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

#ifndef ZAMARA_MPQ_MPQ_H_
#define ZAMARA_MPQ_MPQ_H_

#include <string>
#include <string.h>
#include <stdint.h>
#include <fstream>
#include <vector>

#include "zamara/mpq/mpq_file.h"
#include "zamara/mpq/mpq_user_data.h"
#include "zamara/mpq/mpq_hash_entry.h"
#include "zamara/mpq/mpq_block_entry.h"

namespace zamara {
	namespace mpq {

class Mpq {
 public:
	Mpq();
	~Mpq();

	void Load(std::string filename);
	void Load();
	void Close();
	bool IsLoaded();

	MpqFile GetFile(std::string filename);

	MpqHeader header();
	MpqUserData* user_data();

	std::vector<MpqFile> files();

 private:
 	MpqHashEntry* GetHashEntry(std::string filename);
	bool HasUserData();

	void ReadHeader();
	void ReadHashTable();
	void ReadBlockTable();
	void ReadFiles();

	MpqHeader header_;
	MpqUserData* user_data_;
	uint32_t archive_offset_;

	std::vector<MpqHashEntry> hash_table_;
	std::vector<MpqBlockEntry> block_table_;

	std::vector<MpqFile> files_;

	std::string file_path_;
	std::ifstream file_;
};

	}
}

#endif // ZAMARA_MPQ_MPQ_H_
