#include <iostream>
#include <fstream>

#include "zamara/mpq/mpq.h"
#include "zamara/exception/zamara_exception.h"

using namespace zamara::exception;

namespace zamara
{
	namespace mpq
	{

Mpq::Mpq() { Mpq(""); }

Mpq::Mpq(std::string filePath)
{
	m_filePath = filePath;
}

Mpq::~Mpq()
{
	if (IsLoaded())
	{
		Close();
	}
}

void Mpq::Load(std::string filePath)
{
	m_filePath = filePath;
	Load();
}

void Mpq::Load()
{
	if (IsLoaded())
	{
		Close();
	}
	m_file.open(m_filePath.c_str(), std::ios::in | std::ios::binary);

	if (!IsLoaded())
	{
		throw ZamaraException("Could not find file.",
					ZamaraException::FILE_NOT_FOUND);
	}
    
	char magic[3];
	m_file.read(magic, 3);
	if ((*magic) == 0x4d5051) // Check that the file starts with "MPQ"
	{
        	throw ZamaraException("File is not an MPQ.",
					ZamaraException::FILE_NOT_MPQ);
	}
}

void Mpq::Close()
{
	if (m_file != NULL)
	{
		m_file.close();
	}
}

bool Mpq::IsLoaded()
{
    if (m_file)
    {
        return m_file.is_open();
    }
    return false;
}

	}
}
