#pragma once
#include "Commit.h"
#include "Crypto.h"
class RSA_openssl: public Crypto
{
public:
	RSA_openssl();
	~RSA_openssl();
	string RSA_128_decrypt(string keyFileName, string data_encrypt);
	char* my_decrypt(char *str, char *path_key);
};

