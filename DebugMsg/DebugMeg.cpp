// DebugMeg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>

int main()
{
	LPWSTR szTemp[1024];
	wsprintf((LPWSTR)szTemp, TEXT("Current filename %s\n"), __FILE__);
	OutputDebugString((LPCWSTR)szTemp);
	wsprintf((LPWSTR)szTemp, TEXT("%d line's content is printf(szTemp);\n"), __LINE__ - 1);
	OutputDebugString((LPCWSTR)szTemp);
	wsprintf((LPWSTR)szTemp, TEXT("Complier time :%s %s\n"), __DATE__ , __TIME__);
	OutputDebugString((LPCWSTR)szTemp);
	wsprintf((LPWSTR)szTemp, TEXT("This last fresh time:%s\n"), __TIMESTAMP__);
	OutputDebugString((LPCWSTR)szTemp);

	return 0;
}

