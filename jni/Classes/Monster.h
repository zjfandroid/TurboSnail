#ifndef _SNAIL_MONSTER_H
#define _SNAIL_MONSTER_H

#include "cocos2d.h"
#include "ActionSprite.h"
#include "CMImage.h"
#include "StringUtils.h"

USING_NS_CC;

class Monster : public ActionSprite
{
public:
	struct AnimData
	{
		AnimationUtils::AnimationData monster_idle;
		AnimationUtils::AnimationData monster_defy;
		AnimationUtils::AnimationData monster_change_tomato;
	};

public:
	Monster();
	~Monster();

	void setMonsterType(int type);
	void actionFinishToHide();
	void changeToTomato();//±ä·¬ÇÑ
	bool init();
	CREATE_FUNC(Monster);
	CC_SYNTHESIZE(bool, isRightAns, RightAns);
	CC_SYNTHESIZE(string, mText, Text);
	CC_SYNTHESIZE(CCSprite *, option, Option);
	CC_SYNTHESIZE(CCLabelTTF *, pLabel, Label);

	void hideOption();
	void actionTomatoEat(float xOffSet);
	void actionFinishToEat();
	void actionHitToFar();
private:
	int monsterType;
};

#endif

