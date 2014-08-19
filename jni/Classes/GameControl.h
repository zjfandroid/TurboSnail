#ifndef __TURBO_GAME_CONTROL_H__
#define __TURBO_GAME_CONTROL_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Resource.h"
#include "StartScene.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "MarketScene.h"
#include "ScoreScene.h"
#include "HudLayer.h"
#include "GameLayer.h"
#include "Hero.h"
#include "Monster.h"
#include "PopupLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

class GameControl
{
public:
	struct CARD
	{
		int card_change;
		int card_tips;
		int card_next;
		int card_speed_up;
		int card_ans;
		int card_double;
	};

public:
	GameControl();
	~GameControl();

	bool load(void);
	bool save(void);
	void initResource(void);
	void setSRand(void);
	void reset();

	void playBGMusic(const char* pszFilePath);
	void stopBGMusic(void);
	void playEffect(const char* pszFilePath);

	//远近中景层移动速度
	CC_SYNTHESIZE(float, m_fSkyVelocity, SkyVelocity);
	CC_SYNTHESIZE(float, m_fMidVelocity, MidVelocity);
	CC_SYNTHESIZE(float, m_fRoadVelocity, RoadVelocity);

	CCLabelAtlas * creatLabelAtlas(int number, const LabelAtlasData s_pNumTitleScore, CCNode *parent, int tag = 0);
public:
	map<string, void *> m_Resource;
	int gameState;

	bool isInit;
	bool m_bSound;

	int m_nRight;
	int m_nWrong;
	int m_nScore;
	int m_nCoin;

	int m_nTotalScore;
	int m_nRank;

	float m_fSpeedGain;

	int cards[CARD_COUNT];

	DataControl *dataControl;
};

extern GameControl g_Control;

#endif
