#ifndef __ANIM_UTIL_H__
#define __ANIM_UTIL_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class AnimationUtils
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
	AnimationUtils() {};
	~AnimationUtils() {};

	static CCAnimation* createAnimationWithSpriteFrames(AnimationData animData, int monsterType = -1);
};

#endif
