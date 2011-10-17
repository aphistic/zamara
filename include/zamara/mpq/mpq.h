#ifndef _MPQ_H
#define _MPQ_H

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

namespace zamara
{
	namespace mpq
	{

class Mpq
{
public:
	Mpq();
	Mpq(std::string);
	~Mpq();

	void Load(std::string);
	void Load();

	void Close();

	bool IsLoaded();

private:
	std::string m_filePath;
	std::ifstream m_file;
};
	}
}


#endif
