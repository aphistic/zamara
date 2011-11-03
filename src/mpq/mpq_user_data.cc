#include <string.h>

#include "zamara/mpq/mpq_user_data.h"
#include "zamara/endian/endian.h"

using namespace zamara::endian;

namespace zamara
{
	namespace mpq
	{

MpqUserData::MpqUserData(char* userData)
{
	memcpy(&header, userData, sizeof(MpqUserDataHeader));

	header.maxUserDataSize = Endian::leToH32(*((uint32_t*)(userData + 0x04)));
	header.archiveOffset = Endian::leToH32(*((uint32_t*)(userData + 0x08)));
	header.userDataSize = Endian::leToH32(*((uint32_t*)(userData + 0x0C)));
}

	}
}
