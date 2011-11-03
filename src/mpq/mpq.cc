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

Mpq::Mpq(std::string file_path)
{
	user_data_ = 0;
	file_path_ = file_path;
}

Mpq::~Mpq()
{
	delete user_data_;
	user_data_ = 0;

	if (IsLoaded())
	{
		Close();
	}
}

void Mpq::Load(std::string file_path)
{
	file_path_ = file_path;
	Load();
}

void Mpq::Load()
{
	if (IsLoaded())
	{
		Close();
	}
	file_.open(file_path_.c_str(), std::ios::in | std::ios::binary);

	if (!IsLoaded())
	{
		throw ZamaraException("Could not find file.",
							  ZamaraException::FILE_NOT_FOUND);
	}
    
	ReadHeader();
}

void Mpq::Close()
{
	if (file_ != NULL)
	{
		file_.close();
	}
}

bool Mpq::IsLoaded()
{
    if (file_)
    {
        return file_.is_open();
    }
    return false;
}

void Mpq::ReadHeader()
{
	char *buffer = new char[8]; // A buffer big enough to read up to 64 bits of data
	
	file_.read(buffer, 4);
	if (strncmp(buffer, "MPQ", 3)) // Check that the file starts with "MPQ"
	{
		Close();
		throw ZamaraException("File is not an MPQ.",
							  ZamaraException::FILE_NOT_MPQ);
	}

	if (buffer[3] == 0x1B)
	{
		// This is the user data portion of the file.
		
		uint32_t user_header_size;
		uint32_t user_archive_size;

		// Header Size
        	file_.read(buffer, 4);
	        user_header_size = Endian::LeToH32(*((uint32_t*) buffer));

	        // Archive Size
	        file_.read(buffer, 4);
	        user_archive_size = Endian::LeToH32(*((uint32_t*) buffer));

		file_.seekg(0, ios::beg);
		
		char *user_buffer = new char[user_archive_size];

		file_.read(user_buffer, user_archive_size);

		user_data_ = new MpqUserData(user_buffer);

		file_.read(buffer, 4);

		delete[] user_buffer;
	}


	// Header Size
	file_.read(buffer, 4);
	header_.header_size = Endian::LeToH32(*((uint32_t*) buffer));

	delete[] buffer;

	// Make a new buffer to read the rest of the header
	buffer = new char[header_.header_size - 4]; // Already read 4 bytes of header
	file_.read(buffer, header_.header_size - 4);	

	// Archive Size
	header_.archive_size = Endian::LeToH32(*((uint32_t*) buffer));

	delete[] buffer;
}

bool Mpq::HasUserData()
{
	if (user_data_)
	{
		return true;
	}
	return false;
}

MpqHeader Mpq::header()
{
	return header_;
}

MpqUserData* Mpq::user_data()
{
	return user_data_;
}

	}
}
