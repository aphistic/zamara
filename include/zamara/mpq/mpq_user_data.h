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
	uint32_t m_headerSize;
	uint32_t m_archiveSize;

protected:
	MpqUserData(void* userData);

public:
	friend class Mpq;

};

	}
}


#endif
