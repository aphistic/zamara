#include "zamara/mpq/mpq_user_data.h"
#include "zamara/endian/endian.h"

using namespace zamara::endian;

namespace zamara
{
	namespace mpq
	{

MpqUserData::MpqUserData(char* userData)
{
	m_maxUserDataSize = Endian::LeToH32(*((uint32_t*)(userData + 0x04)));
	m_archiveOffset = Endian::LeToH32(*((uint32_t*)(userData + 0x08)));
	m_userDataSize = Endian::LeToH32(*((uint32_t*)(userData + 0x0C)));
}

uint32_t MpqUserData::getMaxUserDataSize()
{
	return m_maxUserDataSize;
}

uint32_t MpqUserData::getArchiveOffset()
{
	return m_archiveOffset;
}

uint32_t MpqUserData::getUserDataSize()
{
	return m_userDataSize;
}

	}
}
