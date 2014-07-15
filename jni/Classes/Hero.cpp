#include "GameControl.h"

Hero::Hero():
speedLevel(3)
{
}

Hero::~Hero()
{
}

bool Hero::init()
{
	bool bRet = false;
	do 
	{
		AnimData *p = (AnimData*)g_Control.m_Resource["Hero"];
		char ch[32] = {0};
		sprintf(ch, p->hero_speed.m_strPath.c_str(), speedLevel, 0);
		this->initWithFile(ch);
		this->setPosition(p->hero_speed.m_Position);

		CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(p->hero_speed, speedLevel);
		this->setIdleAction(CCRepeatForever::create(CCAnimate::create(animation)));
		setCurSpeed(speedLevel);

		animation = AnimationUtils::createAnimationWithSpriteFrames(p->hero_hit);
		this->setHitAction(CCRepeatForever::create(CCAnimate::create(animation)));
		//CCFiniteTimeAction *actionOne = CCSequence::create(
		//	CCAnimate::create(animation),
		//	CCCallFunc::create(this, callfunc_selector(Monster::idle)),
		//	NULL
		//	);
		//this->setHitAction(actionOne);

		animation = AnimationUtils::createAnimationWithSpriteFrames(p->hero_speed_up);
		CCFiniteTimeAction *actionOne = CCSequence::create(
			CCAnimate::create(animation),
			CCCallFunc::create(this, callfunc_selector(Monster::idle)),
			NULL
			);
		this->setSpeedUpAction(actionOne);

		bRet = true;
	} while (0);

	return bRet;
}

bool Hero::changeSpeed(bool isSpeedUp)
{
	bool isSpeedChange = true;

	if (isSpeedUp && speedLevel < MAX_SPEED_LEVEL)
	{
		speedLevel++;

	}
	else if (!isSpeedUp && speedLevel>0)
	{
		speedLevel--;
	}
	else
	{
		isSpeedChange = false;
	}

	if (isSpeedChange)
	{
		if (speedLevel == 0)
		{
			this->stopAllActions();
		}
		else
		{
			AnimData *p = (AnimData*)g_Control.m_Resource["Hero"];
			CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(p->hero_speed, speedLevel);
			this->setIdleAction(CCRepeatForever::create(CCAnimate::create(animation)));
			setCurSpeed(speedLevel);
			this->idle();
			CCLog("speed level = %d", speedLevel);	
		}
	}
	
	return isSpeedChange;
}

void Hero::setCurSpeed(int speedLevel)
{
	float speedbase = speedLevel * 3;
	g_Control.setSkyVelocity(speedbase * STEP_SPEED_SKY);
	g_Control.setMidVelocity(speedbase * STEP_SPEED_MID);
	g_Control.setRoadVelocity(speedbase * STEP_SPEED_ROAD);
}
