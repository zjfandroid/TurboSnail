#include "GameControl.h"

GameControl g_Control;

GameControl::GameControl() :
	m_bSound(true),
	isInit(false),
	m_nRight(0),
	m_nWrong(0),
	m_nScore(0),
	m_nRank(0),
	m_nCoin(0),
	m_fSpeedGain(1)
{
	//initResource();
};

GameControl::~GameControl()
{
	delete dataControl;
}

void GameControl::initResource(void)
{
	CCLog("init_____________");
	setSRand();
	m_Resource.insert(map<string, void*>::value_type("HudLayer", (void *)(&HudResources)));
	m_Resource.insert(map<string, void*>::value_type("Hero", (void *)(&HeroImages)));
	m_Resource.insert(map<string, void*>::value_type("Monster", (void *)(&MonsterImgs)));
	dataControl = new DataControl();
}

void GameControl::setSRand(void)
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv, NULL);
	unsigned long int rand_seed = psv.tv_sec*1000 + psv.tv_usec/1000;
	srand(rand_seed);
}

void GameControl::playBGMusic(const char* pszFilePath)
{
	if (m_bSound)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, true);
	}
}

void GameControl::stopBGMusic(void)
{
	if (m_bSound)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}

void GameControl::playEffect(const char* pszFilePath)
{
	if (m_bSound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath);
	}
}

CCLabelAtlas * GameControl::creatLabelAtlas(int number, const LabelAtlasData data, CCNode *parent, int tag)
{
	char num[32] = {};
	sprintf(num, "%d", number);
	CCLabelAtlas *pTextLabel = CCLabelAtlas::create(num, data.charMapFile,
		data.itemWidth, data.itemHeight, data.startCharMap);
	if (NULL != pTextLabel)
	{
		pTextLabel->setTag(tag);
		pTextLabel->setPosition(data.m_Position);
		parent->addChild(pTextLabel);
	}

	return pTextLabel;
}

bool GameControl::save(void)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(s_keyCoin, m_nCoin);

	for (int n = 0; n < CARD_COUNT; n++)
	{
		char key[8] = { 0 };
		sprintf(key, s_keyCard, n);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(key, cards[n]);
	}

	CCUserDefault::sharedUserDefault()->flush();
	return true;
}

bool GameControl::load(void)
{
	m_nCoin = CCUserDefault::sharedUserDefault()->getIntegerForKey(s_keyCoin);

	for (int n = 0; n < CARD_COUNT; n++)
	{
		char key[8] = { 0 };
		sprintf(key, s_keyCard, n);
		cards[n] = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
	}

	return true;
}

void GameControl::reset()
{
	m_nRight = 0;
	m_nWrong = 0;
	m_nScore = 0;
}
