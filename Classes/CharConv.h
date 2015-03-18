
#include "cocos2d.h"

char* toUTF(const char* strGB2312)
{
	int iLen = MultiByteToWideChar(CP_ACP, 0, strGB2312, -1, NULL, 0);

	wchar_t* wstr = new wchar_t[iLen + 1];
	memset(wstr, 0, iLen + 1);
	MultiByteToWideChar(CP_ACP, 0, strGB2312, -1, wstr, iLen);
	iLen = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);

	char* strUTF8 = new char[iLen + 1];
	memset(strUTF8, 0, iLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, strUTF8, iLen, NULL, NULL);
	if (wstr) delete[] wstr;

	return strUTF8;
}

