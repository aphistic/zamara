#ifndef ZAMARA_MPQ_MPQ_H_
#define ZAMARA_MPQ_MPQ_H_

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
	MpqHeader header;

	Mpq(std::string = "");
	~Mpq();

	void load(std::string);
	void load();

	void close();

	bool isLoaded();

	bool hasUserData();
	MpqUserData* getUserData();

private:
	MpqUserData* m_userData;

	std::string m_filePath;
	std::ifstream m_file;

	void readHeader();
};
	}
}


#endif // ZAMARA_MPQ_MPQ_H_
