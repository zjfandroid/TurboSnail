#include "GameControl.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

bool Monster::init()
{
	return true;
}

void Monster::setMonsterType(int type)
{
	monsterType = type;
	
	AnimData *p = (AnimData*)g_Control.m_Resource["Monster"];
	char szFileName[32] = { 0 };
	sprintf(szFileName, p->monster_idle.m_strPath.c_str(), monsterType, 0);
	this->initWithFile(szFileName);

	CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(p->monster_idle, monsterType);
	this->setIdleAction(CCRepeatForever::create(CCAnimate::create(animation)));
	this->setPosition(p->monster_idle.m_Position);

	animation = AnimationUtils::createAnimationWithSpriteFrames(p->monster_defy, monsterType);
	this->setDefyAction(CCRepeatForever::create(CCAnimate::create(animation)));

	option = CCSprite::create(s_pPathBgOption);
	option->setPosition(ccp(getContentSize().width * 0.5f + 20, getContentSize().height + 20));
	addChild(option);
	
	pLabel = CCLabelTTF::create("", "Arial", SIZE_OPTION_TXT);

	if (NULL != pLabel)
	{
		pLabel->setColor(COLOR_OPTION);
		pLabel->setPosition(ccp(option->getContentSize().width * 0.5f, option->getContentSize().height *0.5f + 12));
		string gbkStr(getText());
		//StringUtils::GBKToUTF8(gbkStr);
		pLabel->setString(gbkStr.c_str());

		option->addChild(pLabel);
	}
}

void Monster::actionFinishToHide()
{
	this->_actionState = kActionStateHide;
	this->setVisible(false);
}

void Monster::hideOption()
{
	option->setVisible(false);
}

void Monster::changeToTomato()
{
	if (kActionStateChangeToTomato != _actionState)
	{
		_actionState = kActionStateChangeToTomato;
		AnimData *p = (AnimData*)g_Control.m_Resource["Monster"];
		CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(p->monster_change_tomato);
		CCMoveTo *move = CCMoveTo::create(1.0f, ccp(s_pNumTitleCoin.m_Position.x + 135, s_pNumTitleCoin.m_Position.y));

		CCFiniteTimeAction *actionOne = CCSequence::create(
			CCAnimate::create(animation),
			NULL
			);

		this->stopAllActions();
		this->runAction(actionOne);
	}
}

void Monster::actionTomatoEat(float xOffSet)
{
	if (_actionState != kActionStateTomatoEat)
	{
		_actionState = kActionStateTomatoEat;
		CCLog("actionTomatoEat %d", xOffSet);
		CCMoveTo *move = CCMoveTo::create(0.6f, ccp(s_pNumTitleCoin.m_Position.x - 50, s_pNumTitleCoin.m_Position.y));
		//CCMoveTo *move = CCMoveTo::create(1.0f, s_pNumTitleCoin.m_Position);

		CCFiniteTimeAction *actionOne = CCSequence::create(
			CCSpawn::create(CCScaleTo::create(0.6f, 0.2f), move, NULL),
			CCCallFunc::create(this, callfunc_selector(Monster::actionFinishToEat)),
			NULL
			);

		this->runAction(actionOne);
	}
}

void Monster::actionFinishToEat()
{
	g_Control.m_nCoin++;
	actionFinishToHide();
}

void Monster::actionHitToFar()
{
	if (_actionState != kActionStateTomatoEat)
	{
		_actionState = kActionStateTomatoEat;
		hideOption();

		CCMoveTo *move = CCMoveTo::create(0.6f, s_pNumTitleTime.m_Position);
		CCRotateBy *rotate = CCRotateBy::create(0.6f, 960);

		CCFiniteTimeAction *actionOne = CCSequence::create(
			CCSpawn::create(rotate, CCScaleTo::create(0.6f, 0.2f), move, NULL),
			CCCallFunc::create(this, callfunc_selector(Monster::actionFinishToHide)),
			NULL
			);

		this->stopAllActions();
		this->runAction(actionOne);
	}
}
