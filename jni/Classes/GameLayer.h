#ifndef _TURBO_GAMELAYER_H
#define _TURBO_GAMELAYER_H

#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
#include "DataControl.h"

USING_NS_CC;

class GameLayer : public cocos2d::CCLayer
{
public:
	enum Z_ORDER
	{
		ORDER_QUESTION = 100,
		ORDER_MONSTER,
		ORDER_HERO,
		ORDER_COUNT_DOWN,
		ORDER_MENU,
		ORDER_POP,
	};

	/*累计答对多少题过关*/
//	enum LEVEL_UP
//	{
//		LEVEL_ONE = 2,
//		LEVEL_TWO = 5,
//		LEVEL_THREE = 8,
//		LEVEL_FOUR = 12,
//	};

	enum LEVEL_UP
	{
		LEVEL_ONE = 20,
		LEVEL_TWO = 70,
		LEVEL_THREE = 170,
		LEVEL_FOUR = 370,
	};
public:
	GameLayer();
	~GameLayer();

	bool init();
	void initHero();
	void initMonster();
	void initQuestion();
	void initProgress();
	void ansRight();//回答正确

	CREATE_FUNC(GameLayer);

	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void update(float dt);
	void updateTitle();

	CCRect getRect(CCNode* pNode);

	void setSpeedProgress(int speedLevel);
	void ansWrong();
	void initTitle();
	void countDown(int param1);
	void countDownDone();
	void nextQuestion();
	void initCards();

	void onPauseClick(CCObject *pSender);
	void onCardClick(CCObject *pSender);
	void buttonCallback(CCNode *pNode);

	void playSpeedUpAnim();
	void animFinish();

	void changeQuestion();
	void excludeAnswer();
	void noAnswer();
	void noAnswerCard();
	void speedUpCard();
	void showRightAnsCard();
	void dobuleScoreCard();
	bool isLevelUp();
	void levelUpDone();
	void gameOver(bool isPassAll);
	void exitGame();
	void addScore();
	void handleTimeOver();
	void setSpeedGain(int param1);
private:
	Hero *_hero;
	CCArray *monsters;
	DataControl *dataControl;
	bool isAnsRight;
	bool isShowAnswerAfterWrong;
	int doubleScoreCount;
	int gameLevel;
	float timeMax;
	float timeRemain;

	CCProgressTimer *speedProgress;
	CCProgressTimer *timeProgress;
};

#endif
