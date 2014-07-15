#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "iconv\iconv.h"
#else
#include "../../../../libiconv/include/iconv.h"
#endif

USING_NS_CC;
using namespace std;

class StringUtils
{
public:

	struct AnimationData
	{
		string m_strPath;
		CCPoint m_Position;
		int m_frameCount;
		CCRect rect;
		float delay;
	};

public:
	StringUtils() {};
	~StringUtils() {};

	static int GBKToUTF8(string &gbkStr);
};

#endif
