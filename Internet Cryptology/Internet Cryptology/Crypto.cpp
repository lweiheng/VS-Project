#include "stdafx.h"
#include "Commit.h"
#include "Crypto.h"

Crypto::Crypto()
{
}


Crypto::~Crypto()
{
}

string Crypto::read_file(string filename)
{
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

bool Crypto::write_file(string filename, string data)
{
	fstream file1;

	file1.open("1.txt", ios::out | ios::ate);

	file1 << data.data();

	file1.close();

	ofstream file;

	file.open(filename.data(), ios::out|ios::binary);
	
	if (!file)
	{
		cout << "file open file...." << endl;
		return false;
	}

	//cout << "Open File" << endl;

	file << data.c_str();

	file.close();

	return true;
}

void Crypto::string_to_hexstr(string str)
{
	int strLen = str.length();

	for (int i = 0; i < strLen; i++)
	{
		cout << hex << (int)(unsigned char)(str.c_str()[i]);
	}
	cout << endl;
}
