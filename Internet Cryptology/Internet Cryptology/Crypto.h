#pragma once
#include "Commit.h"
class Crypto
{
public:
	Crypto();
	~Crypto();
	string read_file(string filename);
	bool write_file(string filename, string data);
	void string_to_hexstr(string str);
};

