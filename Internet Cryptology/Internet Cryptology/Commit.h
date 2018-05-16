#pragma once
#include "stdafx.h"
#include <iostream>
#include <typeinfo>
#include <openssl\evp.h>
#include <openssl\err.h>
#include <openssl\aes.h>
#include <openssl\ssl.h>
#include <openssl\x509.h>
#include <openssl\md5.h>
#include <istream>
#include <fstream>
#include <ostream>
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")
using namespace std;