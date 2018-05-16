#include "stdafx.h"
#include "RSA_openssl.h"


RSA_openssl::RSA_openssl()
{
}


RSA_openssl::~RSA_openssl()
{
}



string RSA_openssl::RSA_128_decrypt(string keyFileName, string data_encrypt)
{

	BIO * bio_struct;
	RSA * prikey_struct;
	FILE * read_file;

	// 使用bio方式读取key file
	bio_struct = BIO_new_file(keyFileName.data() , "rb");

	prikey_struct = PEM_read_bio_RSAPrivateKey(bio_struct, NULL, NULL, NULL);

	// 将key的分析写入文件中
	bio_struct = BIO_new_file("./test1.txt", "wb");

	RSA_print(bio_struct, prikey_struct, 11);

	cout << "The analyse of the key is in test1.txt at current dir." << endl;

	BIO_free(bio_struct);

	bio_struct = NULL;

	// 取密钥长度
	int rsa_len = RSA_size(prikey_struct);

	cout << "RSA private key len :" << rsa_len << endl;

	unsigned char * de = (unsigned char *)malloc(rsa_len+1);

	memset(de, 0, rsa_len+1);

	// 使用RSA私钥进行解密
	int len = RSA_private_decrypt(rsa_len, (unsigned char *)(data_encrypt.data()), (unsigned char *)de, prikey_struct, RSA_PKCS1_PADDING);

	// 将解密结果转化为string类型
	string detext = (const char *)(char *)de;

	// cout << "RSA Decrypt Result: " << detext.data() << endl;

	return detext;
}

char * RSA_openssl::my_decrypt(char * str, char * path_key)
{
	errno_t err;
	char *p_de;
	RSA *p_rsa;
	FILE *file;
	int rsa_len;
	if ((err = fopen_s(&file, path_key, "r")) != 0) {
		perror("open key file error");
		return NULL;
	}
	if ((p_rsa = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL)) == NULL) {
		ERR_print_errors_fp(stdout);
		return NULL;
	}
	rsa_len = RSA_size(p_rsa);
	p_de = (char *)malloc(rsa_len + 1);
	memset(p_de, 0, rsa_len + 1);
	if (RSA_private_decrypt(rsa_len, (unsigned char *)str, (unsigned char*)p_de, p_rsa, RSA_NO_PADDING)<0) {
		return NULL;
	}
	RSA_free(p_rsa);
	fclose(file);
	return p_de;
}
