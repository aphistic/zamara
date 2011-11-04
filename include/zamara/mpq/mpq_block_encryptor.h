#ifndef ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
#define ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_

#include <string>
#include <stdint.h>

namespace zamara {
	namespace mpq {

class MpqBlockEncryptor {
 public:
 	MpqBlockEncryptor();
	MpqBlockEncryptor(std::string key, uint16_t offset,
										uint32_t buffer, uint32_t size);
	~MpqBlockEncryptor();

	static uint32_t HashString(std::string key, uint16_t offset);

	uint32_t HashString();
	void Decrypt();
	void Encrypt();

	void set_key(std::string key);
	std::string key();
	
	void set_offset(uint16_t offset);
	uint16_t offset();

	void set_buffer(uint32_t buffer);
	uint32_t buffer();

	void set_size(uint32_t size);
	uint32_t size();

	uint32_t* encryption_table();

 private:
 	void GenerateEncryptionTable();

 	uint32_t* encryption_table_;
	std::string key_;
	uint16_t offset_;
	uint32_t buffer_;
	uint32_t size_;
};

	}
}



#endif // ZAMARA_MPQ_MPQ_BLOCK_ENCRYPTOR_H_
