#include "StringUtils.h"

int StringUtils::GBKToUTF8(string &gbkStr)
{
	if (gbkStr.empty())
	{
		return 0;
	}

	iconv_t iconvH;

	iconvH = iconv_open("UTF-8", "GB18030");
	if (iconvH == 0)
	{
		return -1;
	}
	const char* strChar = gbkStr.c_str();
	const char** pin = &strChar;

	size_t strLength = gbkStr.length();
	char* outbuf = (char*)malloc(strLength * 4);
	char* pBuff = outbuf;
	memset(outbuf, 0, strLength * 4);
	size_t outLength = strLength * 4;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
#else
	if (-1 == iconv(iconvH, (char **)pin, &strLength, &outbuf, &outLength))
#endif
	{
		iconv_close(iconvH);
		return -1;
	}
	gbkStr = pBuff;
	iconv_close(iconvH);

	return 0;
}