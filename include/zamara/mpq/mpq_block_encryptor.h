#ifndef ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
#define ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_

#include <string>
#include <stdint.h>

namespace zamara
{
	namespace mpq
	{

class MpqBlockEncryptor
{
public:
	MpqBlockEncryptor(std::string, uint32_t);
	~MpqBlockEncryptor();

	void decrypt();
	void encrypt();
	void hashString();

private:
	uint32_t m_key;
	uint32_t m_offset;
	uint32_t m_buffer;
	uint32_t m_size;

};

	}
}



#endif // ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
