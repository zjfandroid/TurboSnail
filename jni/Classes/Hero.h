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
		MAX_SPEED_LEVEL = 5,//蜗牛速度最大等级
		STEP_SPEED_ROAD = -20,//近景道路每级速度增量
		STEP_SPEED_MID = -10,//中间风景层每级速度增量
		STEP_SPEED_SKY = -6,//远景天空每级速度增量
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

