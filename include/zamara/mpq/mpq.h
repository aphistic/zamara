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
	Mpq(std::string = "");
	~Mpq();

	void Load(std::string);
	void Load();

	void Close();

	bool IsLoaded();

	bool HasUserData();

	MpqHeader header();
	MpqUserData* user_data();

private:
	MpqHeader header_;
	MpqUserData* user_data_;

	std::string file_path_;
	std::ifstream file_;

	void ReadHeader();
};
	}
}


#endif // ZAMARA_MPQ_MPQ_H_
