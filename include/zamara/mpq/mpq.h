#ifndef _MPQ_H
#define _MPQ_H

#include <string>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <fstream>

#include "zamara/mpq/mpq_user_data.h"

namespace zamara
{
	namespace mpq
	{

class Mpq
{
public:
	Mpq(std::string = "");
	~Mpq();

	void Load(std::string);
	void Load();

	void Close();

	bool IsLoaded();

	uint32_t GetHeaderSize();
	uint32_t GetArchiveSize();

	bool hasUserData();
	MpqUserData* getUserData();

private:
	MpqUserData *m_userData;
	
	std::string m_filePath;
	std::ifstream m_file;

	uint32_t m_headerSize;
	uint32_t m_archiveSize;
	uint16_t m_formatVersion;
	uint8_t m_sectorSizeShift;
	uint32_t m_hashTableOffset;
	uint32_t m_blockTableOffset;
	uint32_t m_hashTablEntries;
	uint32_t m_blockTableEntries;

	void ReadHeader();
};
	}
}


#endif
