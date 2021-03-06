// INIfile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>

int main()
{
	WCHAR inBuf[80];
	HKEY hkey1, hkey2;
	DWORD dwDisposition;
	LONG lRetCode;
	WCHAR szData[] = L"USR:App Name\\Section1";

	// 创建.ini文件键
	lRetCode = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\IniFileMapping\\appname.ini",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hkey1,
		&dwDisposition
	);

	if (lRetCode != ERROR_SUCCESS)
	{
		printf("Error in creating appname.ini key\n");
		return(0);
	}

	lRetCode = RegSetKeyValue(hkey1,
		L"Section1",
		0,
		REG_SZ,
		szData,
		sizeof(szData));
	
	if (lRetCode != ERROR_SUCCESS)
	{
		printf("Error in setting Section1 value\n");
		lRetCode = RegCloseKey(hkey1);
		if (lRetCode != ERROR_SUCCESS)
		{
			printf("Error in RegCloseKey\n");
			return(0);
		}
	}

	lRetCode = RegCreateKeyEx(HKEY_CURRENT_USER,
		L"App Name",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hkey2,
		&dwDisposition);

	if (lRetCode != ERROR_SUCCESS)
	{
		printf("Error in creating App Name key\n");
		lRetCode = RegCloseKey(hkey2);
		if (lRetCode != ERROR_SUCCESS)
		{
			printf("Error in RegCloseKey\n");
			return(0);
		}
	}

	WritePrivateProfileStringW(NULL, NULL, NULL, L"appname.ini");

	WritePrivateProfileString(L"Section1",
		L"FirstKey",
		L"It all worked out okay.",
		L"appname.ini");

	WritePrivateProfileString(L"Section1",
		L"SecondKey",
		L"By golly, it works.",
		L"appname.ini");

	WritePrivateProfileSection(L"Section1",
		L"ThirdKey = Another Test.",
		L"appname.ini");

	GetPrivateProfileString(L"Section1",
		L"FirstKey",
		L"Bogus Value: Get didn't work",
		(LPWSTR)inBuf,
		80,
		L"appname.ini");

	wprintf(L"%s", inBuf);

	lRetCode = RegCloseKey(hkey1);
	if (lRetCode != ERROR_SUCCESS)
	{
		printf("Error in RegCloseKey\n");
		return(0);
	}

	lRetCode = RegCloseKey(hkey2);
	if (lRetCode != ERROR_SUCCESS)
	{
		printf("Error in RegCloseKey\n");
		return(0);
	}

    return 1;
}

