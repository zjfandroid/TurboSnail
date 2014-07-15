#ifndef __CM_IMAGE_H__
#define __CM_IMAGE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class CMImage
{
public:

	struct ImageData
	{
		string m_strPath;
		CCPoint m_Position;
	};

public:
	CMImage() {};
	~CMImage() {};

	static CCSprite* create(void *data, CCNode *parent, int nZOrder, bool bVisible = true);
	static CCSprite* create(void *data, CCNode *parent, int nZOrder, int nTag, bool bVisible = true);
	static CCSprite* create(void *data, CCNode *parent, int nZOrder, int nTag, const CCPoint& anchor, bool bVisible = true);
};

#endif // __CM_IMAGE_H__
