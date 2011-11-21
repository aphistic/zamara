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
	Mpq(std::string = "");
	~Mpq();

	void Load(std::string filename);
	void Load();
	void Close();
	bool IsLoaded();
	MpqHashEntry* GetHashEntry(std::string filename);
	bool HasUserData();

	MpqHeader header();
	MpqUserData* user_data();

	std::vector<MpqFile> files();

 private:
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
