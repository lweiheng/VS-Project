#include "stdafx.h"
#include "AES.h"
#include "Commit.h"

#define _CRT_SECURE_NO_WARNINGS
AES::AES()
{
}


AES::~AES()
{
}

string AES::EVP_AES_128_encrypt(string clearText, string key_16, string iv_16, string workMode)
{

	// 生成密钥和初始向量
	unsigned char *key = (unsigned char *)(key_16.data());
	unsigned char *iv = (unsigned char *)(iv_16.data());

	//const char *inStr = "this is test string,haha";
	// 此处为需要加密的明文
	const char *inStr = clearText.data();
	// 记录明文长度
	int inLen = strlen(inStr);
	// 定义变量
	int encLen = 0;
	// 定义变量
	int outlen = 0;
	// 定义缓冲区，用于存储加密后的字符串
	unsigned char encData[1024];

	// 打印明文
	printf("\tsource:\t%s\n", inStr);

	// 加密函数
	EVP_CIPHER_CTX *ctx;
	// 初始化加密算法数据结构对应的空间
	ctx = EVP_CIPHER_CTX_new();

	// 将加密算法和密钥，初始向量，写入数据结构
	if (workMode.compare("CBC") == 0)
	{
		EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv, 1);
	}
	else
	{
		EVP_CipherInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv, 1);
	}
	
	// 进行加密，将加密后的密文写入设置好的缓冲区，函数加密需要指定加密的字符串的长度，同时记录加密后的字符串长度
	EVP_CipherUpdate(ctx, encData, &outlen, (unsigned char*)inStr, inLen);
	// 记录加密后的字符串的长度
	encLen = outlen;
	//printf("%d\n", encLen);
	// 释放指针指向的空间，指定需要释放的空间的大小
	EVP_CipherFinal(ctx, encData + outlen, &outlen);
	// 加密后的长度加倍
	encLen += outlen;
	//printf("%d\n", encLen);
	// 释放指针
	EVP_CIPHER_CTX_free(ctx);
	//打印加密后的字符串
	encData[encLen] = '\0';
	//printf("%s\n", encData);

	string cipherText = (const char*) (char *)encData;

	return cipherText;
}

string AES::EVP_AES_128_decrypt(string cipherText, string key_16, string iv_16, string workMode)
{

	// 解密
	// 声明变量存储解密后字符串长度
	int decLen = 0;
	// 输出长度记录变量清零
	int outlen = 0;

	//unsigned char key[32] = { 1 };
	//unsigned char iv[16] = { 0 };
	unsigned char *key = (unsigned char *)(key_16.data());
	unsigned char *iv = (unsigned char *)(iv_16.data());

	// 声明缓冲区
	unsigned char * decData = new unsigned char[cipherText.size()];
	// 声明数据结构
	EVP_CIPHER_CTX *ctx2;
	// 对指针进行初始化
	ctx2 = EVP_CIPHER_CTX_new();

	if (workMode.compare("CBC") == 0)
	{
		EVP_CipherInit_ex(ctx2, EVP_aes_128_cbc(), NULL, key, iv, 0);
	}
	else
	{
		EVP_CipherInit_ex(ctx2, EVP_aes_128_ecb(), NULL, key, iv, 0);
	}

	// 设置指针指向的空间
	//EVP_CipherInit_ex(ctx2, EVP_aes_128_cbc(), NULL, key, iv, 0);
	// 进行加密
	EVP_CipherUpdate(ctx2, decData, &outlen, (unsigned char*)cipherText.data() , cipherText.length());
	decLen = outlen;
	EVP_CipherFinal(ctx2, decData + outlen, &outlen);
	decLen += outlen;
	EVP_CIPHER_CTX_free(ctx2);
	//cout << cipherText.length() << "  "<< decLen << endl;
	decData[decLen] = '\0';
	string clearText = (const char*)(char *)decData;


	AES_KEY roundkeys;
	AES_set_decrypt_key(key, AES_BLOCK_SIZE * 8, &roundkeys);
	AES_cbc_encrypt((unsigned char *)cipherText.data(), decData, cipherText.size(), &roundkeys, iv, AES_DECRYPT);

	FILE * pFile;
	//获取文件指针
	pFile = fopen("2.txt", "wb");
	//向文件写数据
	fwrite(decData, 1, cipherText.size(), pFile);
	fclose(pFile);

	free(decData);
	decData = NULL;

	return clearText;
}

void AES::AEs_128_encrypt_decrypt(const char * from , const char * to)
{
	
	//file length
	int32_t len, align, pointer = 0;
	uint8_t i, *ret, *dec;

	/* 128 bit key */
	uint8_t key[] =
	{
		'e', 'e', 'e', 'e', 'f', 'f', 'f', 'f',
		'g', 'g', 'g', 'g', 'h', 'h', 'h', 'h',
	};
	uint8_t iv[] =
	{
		'e', 'e', 'e', 'e', 'f', 'f', 'f', 'f',
		'g', 'g', 'g', 'g', 'h', 'h', 'h', 'h',
	};

	AES_KEY roundkeys;
	FILE *pFile = NULL;

	FILE *fl = fopen(from, "rb");
	fseek(fl, 0, SEEK_END);
	len = ftell(fl);
	if (len % 8 != 0)
		return;
	align = len;
	ret = (uint8_t *)malloc(align);
	fseek(fl, 0, SEEK_SET);
	fread(ret, 1, len, fl);
	dec = (uint8_t *)malloc(align);

	// key schedule
	AES_set_decrypt_key(key, AES_BLOCK_SIZE * 8, &roundkeys);
	AES_cbc_encrypt(ret, dec, align, &roundkeys, iv, AES_DECRYPT);

	//获取文件指针
	pFile = fopen(to, "wb");
	//向文件写数据
	fwrite(dec, 1, align, pFile);
	fclose(pFile);

	free(ret);
	ret = NULL;
	free(dec);
	dec = NULL;
}
