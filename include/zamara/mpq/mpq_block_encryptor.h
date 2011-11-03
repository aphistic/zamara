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

	void Decrypt();
	void Encrypt();
	void HashString();

private:
	uint32_t key_;
	uint32_t offset_;
	uint32_t buffer_;
	uint32_t size_;

};

	}
}



#endif // ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
