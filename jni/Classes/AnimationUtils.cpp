#include "AnimationUtils.h"

CCAnimation* AnimationUtils::createAnimationWithSpriteFrames(AnimationData animData, int monsterType)
{
	int i;
	CCArray *idleFrames = CCArray::createWithCapacity(animData.m_frameCount);
	for (i = 0; i < animData.m_frameCount; i++)
	{
		CCString *path = NULL;
		if (-1 == monsterType)
		{
			path = CCString::createWithFormat(animData.m_strPath.c_str(), i);
		}
		else
		{
			path = CCString::createWithFormat(animData.m_strPath.c_str(), monsterType, i);
		}
		CCSpriteFrame *frame = CCSpriteFrame::create(path->getCString(), animData.rect);

		idleFrames->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(idleFrames, animData.delay);
	return animation;
}
