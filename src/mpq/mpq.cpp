#include "zamara/mpq/mpq.h"

namespace zamara
{
	namespace mpq
	{

Mpq::Mpq(std::string filePath)
{
	m_file.open(filePath.c_str(), std::ios::in | std::ios::binary);
}

Mpq::~Mpq()
{
	m_file.close();
}

Mpq* Mpq::Load(std::string filePath)
{
	Mpq* loadingMpq = new Mpq(filePath);
}

	}
}
