#include "Commit.h"
#include "Crypto.h"



class AES:public Crypto
{
public:
	AES();
	~AES();
	string EVP_AES_128_encrypt(string clearText, string key_16, string iv_16, string workMode = "CBC");
	string EVP_AES_128_decrypt(string cipherText, string key_16, string iv_16, string workMode = "CBC");
	void AEs_128_encrypt_decrypt(const char * from, const char * to);
};

