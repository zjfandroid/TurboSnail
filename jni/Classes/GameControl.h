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
	struct OCMusicResource
	{
		string m_strBGMusicA;
		string m_strBGMusicB1;
		string m_strBGMusicB2;
		string m_strBGMusicB3;
		string m_strBGMusicC;
		string m_strButton;
		string m_strCountDown;
		string m_strTimePlus;
		string m_strLevelUp;
		string m_strFirstBlood;
		string m_strDobule_kill; 
		string m_strTriple_kill;
		string m_strUltra_kill;
		string m_strRampage;
		string m_strKillingSpree;
		string m_strDominating;
		string m_strMegaKill;
		string m_strUnstoppable;
		string m_strWichedSick;
		string m_strMonsterKill;
		string m_strGodlike;
		string m_strHolyShit;
		string m_strOwning;
		string m_strButcher;
	};
	
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
	enum OCMusicID
	{
		MIDBG_MUSIC_A,
		MIDBG_MUSIC_B1,
		MIDBG_MUSIC_B2,
		MIDBG_MUSIC_B3,
		MIDBG_MUSIC_C,
		MIDBUTTON,
		MIDCOUNT_DOWN,
		MIDTIME_PLUS,
		MIDLEVEL_UP,
		MID_FIRST_BLOOD,
		MID_DOBULE_KILL,
		MID_TRIPLE_KILL, 
		MID_ULTRA_KILL,
		MID_RAMPAGE,
		MID_KILLING_SPREE,
		MID_DOMINATING,
		MID_MEGA_KILL,
		MID_UNSTOPPABLE,
		MID_WICHEDSICK,
		MID_MONSTERKILL,
		MID_GODLIKE,
		MID_HOLYSHIT,
		MID_OWNING,
		MID_BUTCHER,
	};

public:
	GameControl();
	~GameControl();

	bool load(void);
	bool save(void);
	void initResource(void);
	void setSRand(void);
	void reset();

	void playBGMusic(OCMusicID index);
	void stopBGMusic(void);
	void playEffect(OCMusicID index);
	void playEffect(int index);

	//远近中景层移动速度
	CC_SYNTHESIZE(float, m_fSkyVelocity, SkyVelocity);
	CC_SYNTHESIZE(float, m_fMidVelocity, MidVelocity);
	CC_SYNTHESIZE(float, m_fRoadVelocity, RoadVelocity);

	CCLabelAtlas * creatLabelAtlas(int number, const LabelAtlasData s_pNumTitleScore, CCNode *parent, int tag = 0);
public:
	map<string, void *> m_Resource;

	bool m_bSound;

	int m_nRight;
	int m_nWrong;
	int m_nScore;
	int m_nCoin;

	int m_nTotalScore;
	int m_nRank;

	float m_fSpeedGain;

	int cards[CARD_COUNT];
};

extern GameControl g_Control;

#endif
