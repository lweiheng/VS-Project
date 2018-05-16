#pragma once
#include "Commit.h"

#define MAXDATABUFF 1024
#define MD5LENTH 16

class MD5_class
{
public:
	

	MD5_class();
	~MD5_class();
	//string MD5_Encrypt();
	string MD5_Encrypt(string filename);
	string MD5_Decrypt(string MD5value);
};

