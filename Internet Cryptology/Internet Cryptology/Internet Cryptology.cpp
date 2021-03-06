// Internet Cryptology.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Commit.h"
#include "AES.h"
#include "RSA_openssl.h"
#include "MD5_class.h"

int main()
{	


	cout << "\t\t实验一： Bisic" << endl;

	string examText = "Hello OpenSSL";
	examText = examText;
	cout  << "\tCipher Text: \t" << examText.data() << endl;

	cout << "\tkey:\t\taaaabbbbccccdddd" << endl;
	cout << "\tiv:\t\teeeeffffgggghhhh"<< endl;
	cout << "\tWork Mode:\tECB" << endl;
	AES aesInsExam1 = AES();

	string cipherTextExam1 = aesInsExam1.EVP_AES_128_encrypt(examText, "aaaabbbbccccdddd", "eeeeffffgggghhhh", "ECB");
	cout << "\tCipher Text: \t";
	aesInsExam1.string_to_hexstr(cipherTextExam1);
	cout << endl;

	string clearTextExam1 = aesInsExam1.EVP_AES_128_decrypt(cipherTextExam1, "aaaabbbbccccdddd", "eeeeffffgggghhhh", "ECB");
	cout << "\tClear Text: \t" << clearTextExam1.c_str() << endl;
	cout << endl;

	string MD5str = "./StudentIDandName1.txt";
	cout << "\tMD5 file addr and file string: \t" << MD5str.c_str() << endl;
	MD5_class md5_test = MD5_class();
	md5_test.MD5_Encrypt(MD5str);

	cout << endl << endl <<"\t\t实验二： AES-CBC" << endl;

	AES p = AES();
	
	// 将密钥和iv硬编码进代码
	string key = "eeeeffffgggghhhh";
	string iv = "eeeeffffgggghhhh";
	cout << "\tkey:\t\t" << key.c_str() << endl;
	cout << "\tiv:\t\t" << key.c_str() << endl;
	cout << "\tWork Mode:\t" << "CBC" << endl;

	// 获取密文信息
	string cipher = p.read_file("./cipher");

	// 进行解密
	p.AEs_128_encrypt_decrypt("cipher", "clear.mov");

	cout<< endl << endl << "\t\t实验三： 综合加解密" << endl;

	// 声明RSA_openssl实例
	RSA_openssl rsa = RSA_openssl();
	// 读取需要使用RSA私钥进行解密的文件
	string data_encrypt = rsa.read_file("AES_key_encrypted_by_RSA");
	// 进行RSA解密，传入RSA私钥信息和需要解密的数据
	string rsa_decrypt_result = rsa.RSA_128_decrypt("prikey.key", data_encrypt);
	cout << "rsa_decrypt_result: " << rsa_decrypt_result.data() << endl;
	// 使用解密好的AES密钥解密密文并输出
	string temp = p.read_file("AEScipher.txt");

	char * pre_de;
	pre_de = rsa.my_decrypt((char *)data_encrypt.c_str(), "prikey.key");
	printf("%s", pre_de);

	p.AEs_128_encrypt_decrypt("AEScipher.txt","AESclear23.txt");
	p.write_file("./AESclear.txt", p.EVP_AES_128_decrypt(p.read_file("AEScipher.txt"), rsa_decrypt_result, rsa_decrypt_result, "CBC"));
	cout << "The clear text is in ./AESclear.txt at current dir." << endl;

	system("pause");
    return 0;
}