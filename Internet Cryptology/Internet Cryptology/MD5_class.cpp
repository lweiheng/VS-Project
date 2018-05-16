#include "stdafx.h"
#include "MD5_class.h"


MD5_class::MD5_class()
{
}


MD5_class::~MD5_class()
{
}


string MD5_class::MD5_Encrypt(string filename)
{
	ifstream ifile(filename.c_str(), ios::in | ios::binary);

	unsigned char MD5result[MD5LENTH];

	do {
		if (ifile.fail())
		{
			cout << "open file failure! so only display string MD5 !" << endl;
			break;
		}
		MD5_CTX md5_ctx;
		MD5_Init(&md5_ctx);

		char dataBuff[MAXDATABUFF];

		while (!ifile.eof())
		{
			ifile.read(dataBuff, MAXDATABUFF);
			int length = ifile.gcount();
			if (length)
			{
				MD5_Update(&md5_ctx, dataBuff, length);
			}
		}
		MD5_Final(MD5result, &md5_ctx);
		cout << "\tfile MD5:\t" ;

		for (int i = 0; i < MD5LENTH; i++)
		{
			cout << hex << (int)MD5result[i];
		}
		cout << endl;
	} while (false);

	MD5((const unsigned char *)filename.c_str(), filename.size(), MD5result);
	cout << "\tstring MD5:\t";
	for (int i = 0; i < MD5LENTH; i++)
	{
		cout << hex << (int)MD5result[i];
	}
	cout << endl;

	string result = (const char *)MD5result;

	return result;
}

string MD5_class::MD5_Decrypt(string MD5value)
{
	return string();
}
