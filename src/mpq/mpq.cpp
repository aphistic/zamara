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
	m_isLoaded = false;
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

	if (!m_file)
	{
		//throw new ZamaraException("Could not find file.",
		//	ZamaraException::FILE_NOT_FOUND);
		throw std::exception();
	}
	m_isLoaded = true;
}

void Mpq::Close()
{
	if (m_file != NULL)
	{
		m_file.close();
	}
	m_isLoaded = false;
}

bool Mpq::IsLoaded()
{
	return m_isLoaded && m_file;
}

	}
}
