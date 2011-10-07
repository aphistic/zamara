#ifndef _MPQ_H
#define _MPQ_H

#include <string>
#include <iostream>
#include <fstream>

namespace zamara
{
	namespace mpq
	{

class Mpq
{
public:
	~Mpq();

	static Mpq* Load(std::string);
protected:
	Mpq(std::string);
private:
	std::ifstream m_file;
};
	}
}


#endif
