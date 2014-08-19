#pragma once
#ifndef DEFINE_H
#define DEFINE_H
#include "cocos2d.h"

USING_NS_CC;

// 1 - convenience measurements
#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define CENTER ccp(SCREEN.width/2, SCREEN.height/2)
//#define CURTIME do {
//	timeval time;
//	gettimeofday(&time, NULL);
//	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
//	return (float)millisecs;
//} while (0)

// 2 - convenience functions
#define random_range(low, high) (rand() % (high - low + 1)) + low
#define frandom (float)rand() / UINT64_C(0x100000000)
#define frandom_range(low, high) ((high - low) * frandom) + low

// 3 - enumerations
typedef enum _ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateHit,
	kActionStateDefy,
	kActionStateSpeedUp,
	kActionStateChangeToTomato,
	kActionStateTomatoEat,
	kActionStateHide,
} ActionState;

enum GameRunState
{
	GRS_UNKNOWN,
	GRS_PAUSE,
	GRS_PLAY,
	GRS_TOUCH_OVER,
	GRS_FINISH_ANSWER,
	GRS_LEVELUP,
	GRS_OVER
};

enum NUM
{
	CARD_COUNT = 6,//µÀ¾ßÊý
	CARD_INFO = 99,
	BTN_CARD = 100,

	BTN_CLOSE = 200,
	BTN_SURE,
	BTN_CANCLE,
	BTN_BUY,

	LabelAtlas_SCORE,
	LabelAtlas_TIME,
	LabelAtlas_COIN,
	LabelAtlas_PRICE,

	TAG_QUESTION_TITLE = 800,
	TAG_QUESTION_ANS,
	TAG_RIGHT_ANS,
	TAG_WRONG_ANS,
	TAG_CARD_BUY,

	TAG_DARK_BG = 900,
	TAG_COUNTDOWN,
	TAG_MENU,
};

// 4 - structures
typedef struct _BoundingBox {
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
} BoundingBox;

struct ImageData
{
	const char *m_strPath;
	CCPoint m_Position;
};

struct LabelAtlasData
{
	const char *charMapFile;
	int itemWidth;
	int itemHeight;
	int startCharMap;
	CCPoint m_Position;
};

struct MenuItemData
{
	const char *charMapFile;
	const char *charMapFilePress;
	CCPoint m_Position;
};

#endif