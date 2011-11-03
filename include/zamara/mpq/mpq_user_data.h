#ifndef ZAMARA_MPQ_MPQ_USER_DATA_H_
#define ZAMARA_MPQ_MPQ_USER_DATA_H_

#include <stdint.h>

#include "zamara/mpq/mpq_structs.h"

namespace zamara
{
	namespace mpq
	{

class MpqUserData
{
private:

protected:
	MpqUserData(char* userData);

public:
	friend class Mpq;

	MpqUserDataHeader header;

};

	}
}


#endif // ZAMARA_MPQ_MPQ_USER_DATA_H_
