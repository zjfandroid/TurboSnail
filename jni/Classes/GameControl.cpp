#include "GameControl.h"

GameControl g_Control;

GameControl::GameControl() :
	m_bSound(true),

	m_nRight(0),
	m_nWrong(0),
	m_nScore(0),
	m_nRank(0),
	m_nCoin(0),
	m_fSpeedGain(1)
{
	setSRand();
	initResource();
};

GameControl::~GameControl()
{
}

void GameControl::initResource(void)
{
	m_Resource.insert(map<string, void*>::value_type("HudLayer", (void *)(&HudResources)));
	m_Resource.insert(map<string, void*>::value_type("Hero", (void *)(&HeroImages)));
	m_Resource.insert(map<string, void*>::value_type("Monster", (void *)(&MonsterImgs)));
	//m_Resource.insert(map<string, void*>::value_type("GameMusic", (void *)(&GameMusic)));
}

void GameControl::setSRand(void)
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv, NULL);
	unsigned long int rand_seed = psv.tv_sec*1000 + psv.tv_usec/1000;
	srand(rand_seed);
}

void GameControl::playBGMusic(OCMusicID index)
{
	GameControl::OCMusicResource *pMusicRes = (GameControl::OCMusicResource *)(g_Control.m_Resource["GameMusic"]);
	if (m_bSound && (NULL != pMusicRes))
	{
		switch (index)
		{
		case MIDBG_MUSIC_A:
			if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			{
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strBGMusicA.c_str(), true);
			}
			break;

		case MIDBG_MUSIC_B1:
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strBGMusicB1.c_str(), true);
			break;

		case MIDBG_MUSIC_B2:
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strBGMusicB2.c_str(), true);
			break;

		case MIDBG_MUSIC_B3:
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strBGMusicB3.c_str(), true);
			break;

		case MIDBG_MUSIC_C:
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strBGMusicC.c_str(), true);
			break;

		case MIDCOUNT_DOWN:
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusicRes->m_strCountDown.c_str(), false);
			break;

		default:
			break;
		}
	}
}

void GameControl::stopBGMusic(void)
{
	if (m_bSound)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}

void GameControl::playEffect(OCMusicID index)
{
	GameControl::OCMusicResource *pMusicRes = (GameControl::OCMusicResource *)(g_Control.m_Resource["GameMusic"]);
	if (m_bSound && (NULL != pMusicRes))
	{
		switch (index)
		{
		case MIDBUTTON:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strButton.c_str());
			break;

		case MIDTIME_PLUS:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strTimePlus.c_str());
			break;

		case MIDLEVEL_UP:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strLevelUp.c_str());
			break;

		case MID_FIRST_BLOOD:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strFirstBlood.c_str());
			break;

		case MID_BUTCHER:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strButcher.c_str());
			break;
		default:
			break;
		}
	}
}

void GameControl::playEffect(int index)
{
	GameControl::OCMusicResource *pMusicRes = (GameControl::OCMusicResource *)(g_Control.m_Resource["GameMusic"]);
	if (m_bSound && (NULL != pMusicRes))
	{
		switch (index)
		{
		case MID_DOBULE_KILL:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strDobule_kill.c_str());
			break;

		case MID_TRIPLE_KILL:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strTriple_kill.c_str());
			break;

		case MID_ULTRA_KILL:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strUltra_kill.c_str());
			break;

		case MID_RAMPAGE:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strRampage.c_str());
			break;

		case MID_KILLING_SPREE:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strKillingSpree.c_str());
			break;

		case MID_DOMINATING:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strDominating.c_str());
			break;

		case MID_MEGA_KILL:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strMegaKill.c_str());
			break;

		case MID_UNSTOPPABLE:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strUnstoppable.c_str());
			break;

		case MID_WICHEDSICK:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strWichedSick.c_str());
			break;

		case MID_MONSTERKILL:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strMonsterKill.c_str());
			break;

		case MID_GODLIKE:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strGodlike.c_str());
			break;

		case MID_HOLYSHIT:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strHolyShit.c_str());
			break;

		case MID_OWNING:
			SimpleAudioEngine::sharedEngine()->playEffect(pMusicRes->m_strOwning.c_str());
			break;

		default:
			break;
		}
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
	CCLog("________load_________");
	m_nCoin = CCUserDefault::sharedUserDefault()->getIntegerForKey(s_keyCoin);

	for (int n = 0; n < CARD_COUNT; n++)
	{
		char key[8] = { 0 };
		sprintf(key, s_keyCard, n);
		cards[n] = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
	}
	CCLog("________load_________44444444");

	return true;
}

void GameControl::reset()
{
	m_nRight = 0;
	m_nWrong = 0;
	m_nScore = 0;
}
