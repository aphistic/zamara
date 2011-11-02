#ifndef _MPQ_USER_DATA_H
#define _MPQ_USER_DATA_H

#include <stdint.h>

namespace zamara
{
	namespace mpq
	{

class MpqUserData
{
private:
	uint32_t m_maxUserDataSize;
	uint32_t m_archiveOffset;
	uint32_t m_userDataSize;

protected:
	MpqUserData(char* userData);

public:
	friend class Mpq;

	uint32_t getMaxUserDataSize();
	uint32_t getArchiveOffset();
	uint32_t getUserDataSize();

};

	}
}


#endif
