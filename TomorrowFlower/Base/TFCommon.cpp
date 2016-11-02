#include "TFCommon.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <WinSock2.h>

namespace TomorrowFlower {

static const int MAX_LEN = 16*1024;

void TFLog(const char *pszFormat, ...)
{
	static char szBuf[MAX_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
	va_end(ap);

	WCHAR wszBuf[MAX_LEN] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), nullptr, FALSE);
	printf("%s\n", szBuf);
}

void TFMessageBox(const char *pszTitle, const char *pszFormat, ...)
{
	static char szBuf[MAX_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
	va_end(ap);

	MessageBoxA(nullptr, szBuf, pszTitle, MB_OK);
}

}