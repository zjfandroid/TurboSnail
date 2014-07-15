#ifndef _SNAIL_HERO_H
#define _SNAIL_HERO_H
#include "cocos2d.h"
#include "ActionSprite.h"
#include "AnimationUtils.h"

USING_NS_CC;

class Hero : public ActionSprite
{
public:
	struct AnimData
	{
		AnimationUtils::AnimationData hero_speed;
		AnimationUtils::AnimationData hero_speed_up;
		AnimationUtils::AnimationData hero_hit;
	};

	enum HeroConstant
	{
		MAX_SPEED_LEVEL = 5,//��ţ�ٶ����ȼ�
		STEP_SPEED_ROAD = -20,//������·ÿ���ٶ�����
		STEP_SPEED_MID = -10,//�м�羰��ÿ���ٶ�����
		STEP_SPEED_SKY = -6,//Զ�����ÿ���ٶ�����
	};

public:
	Hero();
	~Hero();

	bool init();
	bool changeSpeed(bool isSpeedUp);
	void setCurSpeed(int speedLevel);

	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(int, speedLevel, SpeedLevel);
};

#endif

