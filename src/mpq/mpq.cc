#include <iostream>
#include <fstream>

#include "zamara/mpq/mpq.h"
#include "zamara/endian/endian.h"
#include "zamara/exception/zamara_exception.h"

using namespace std;
using namespace zamara::endian;
using namespace zamara::exception;

namespace zamara
{
	namespace mpq
	{

Mpq::Mpq(std::string filePath)
{
	m_userData = 0;
	m_filePath = filePath;
}

Mpq::~Mpq()
{
	delete m_userData;
	m_userData = 0;

	if (isLoaded())
	{
		close();
	}
}

void Mpq::load(std::string filePath)
{
	m_filePath = filePath;
	load();
}

void Mpq::load()
{
	if (isLoaded())
	{
		close();
	}
	m_file.open(m_filePath.c_str(), std::ios::in | std::ios::binary);

	if (!isLoaded())
	{
		throw ZamaraException("Could not find file.",
							  ZamaraException::FILE_NOT_FOUND);
	}
    
	readHeader();
}

void Mpq::close()
{
	if (m_file != NULL)
	{
		m_file.close();
	}
}

bool Mpq::isLoaded()
{
    if (m_file)
    {
        return m_file.is_open();
    }
    return false;
}

void Mpq::readHeader()
{
	char *buffer = new char[8]; // A buffer big enough to read up to 64 bits of data
	
	m_file.read(buffer, 4);
	if (strncmp(buffer, "MPQ", 3)) // Check that the file starts with "MPQ"
	{
		close();
		throw ZamaraException("File is not an MPQ.",
							  ZamaraException::FILE_NOT_MPQ);
	}

	if (buffer[3] == 0x1B)
	{
		// This is the user data portion of the file.
		
		uint32_t userHeaderSize;
		uint32_t userArchiveSize;

		// Header Size
        	m_file.read(buffer, 4);
	        userHeaderSize = Endian::leToH32(*((uint32_t*) buffer));

	        // Archive Size
	        m_file.read(buffer, 4);
	        userArchiveSize = Endian::leToH32(*((uint32_t*) buffer));

		m_file.seekg(0, ios::beg);
		
		char *userBuffer = new char[userArchiveSize];

		m_file.read(userBuffer, userArchiveSize);

		m_userData = new MpqUserData(userBuffer);

		m_file.read(buffer, 4);

		delete[] userBuffer;
	}


	// Header Size
	m_file.read(buffer, 4);
	header.headerSize = Endian::leToH32(*((uint32_t*) buffer));

	delete[] buffer;

	// Make a new buffer to read the rest of the header
	buffer = new char[header.headerSize - 4]; // Already read 4 bytes of header
	m_file.read(buffer, header.headerSize - 4);	

	// Archive Size
	header.archiveSize = Endian::leToH32(*((uint32_t*) buffer));

	delete[] buffer;
}

bool Mpq::hasUserData()
{
	if (m_userData)
	{
		return true;
	}
	return false;
}

MpqUserData* Mpq::getUserData()
{
	return m_userData;
}

	}
}
