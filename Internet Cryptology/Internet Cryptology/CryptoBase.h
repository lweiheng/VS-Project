#pragma once
#include "Commit.h"
class CryptoBase
{
public:
	CryptoBase();
	~CryptoBase();
	string read_file_to_string(string fileName);
	string write_string_to_file(string fileName);
};

