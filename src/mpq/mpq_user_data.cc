#include <string.h>

#include "zamara/mpq/mpq_user_data.h"
#include "zamara/endian/endian.h"

using namespace zamara::endian;

namespace zamara
{
	namespace mpq
	{

MpqUserData::MpqUserData(char* user_data)
{
	header_.max_user_data_size = Endian::LeToH32(*((uint32_t*)(user_data + 0x04)));
	header_.archive_offset = Endian::LeToH32(*((uint32_t*)(user_data + 0x08)));
	header_.user_data_size = Endian::LeToH32(*((uint32_t*)(user_data + 0x0C)));
}

MpqUserDataHeader MpqUserData::header()
{
	return header_;
}

	}
}
