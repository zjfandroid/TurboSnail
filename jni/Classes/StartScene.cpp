#include "GameControl.h"

USING_NS_CC;

StartScene::StartScene() 
{
}

StartScene::~StartScene()
{
}

bool StartScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		g_Control.playBGMusic(s_musicBgMain);
		//initProgress();
		initBackground();
		initButton();

		if (!g_Control.isInit)
		{
			this->scheduleOnce(schedule_selector(StartScene::initResources), 0);
		}
		isTouchEnable = true;
		bRet = true;
	} while (0);

	return bRet;
}

void StartScene::initBackground()
{
	CCSprite *bg = CCSprite::create(s_pBgMain);
	bg->setPosition(CENTER);
	addChild(bg);

	bg = CCSprite::create(s_pBgLogo.m_strPath);
	bg->setPosition(s_pBgLogo.m_Position);
	addChild(bg);
}

void StartScene::initButton()
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(s_pMenuItemClose.charMapFile, s_pMenuItemClose.charMapFilePress, this, menu_selector(StartScene::buttonCallback));
	if (NULL != pMenuItem)
	{
		pMenuItem->setAnchorPoint(ccp(1,1));
		pMenuItem->setPosition(SCREEN);
		pMenuItem->setTag(BTN_CLOSE);
	}
	CCMenu *pMenu = CCMenu::create(pMenuItem, NULL);
	if (NULL != pMenu)
	{
		pMenu->setPosition(CCPointZero);
		addChild(pMenu);
	}

	CCMenuItemImage *pItem0 = CCMenuItemImage::create(s_pMenuItemSound.charMapFile, s_pMenuItemSound.charMapFilePress);
	CCMenuItemImage *pItem1 = CCMenuItemImage::create(s_pMenuItemSoundDisable.charMapFile, s_pMenuItemSoundDisable.charMapFilePress);
	CCMenuItemToggle *pSound = CCMenuItemToggle::createWithTarget(this, menu_selector(StartScene::buttonCallback), pItem0, pItem1, NULL);
	pSound->setAnchorPoint(ccp(0, 1));
	pSound->setPosition(ccp(0, SCREEN.height));
	pSound->setTag(BTN_SOUND);
	if (!g_Control.m_bSound)
	{
		pSound->setSelectedIndex(1);
	}
	pMenu->addChild(pSound);

	pMenuItem = CCMenuItemImage::create(s_pMenuItemMarket.charMapFile, s_pMenuItemMarket.charMapFilePress, this, menu_selector(StartScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0, 1));
	pMenuItem->setPosition(ccp(0, SCREEN.height - 90));
	pMenuItem->setTag(BTN_MARKET);
	pMenu->addChild(pMenuItem);

	pMenuItem = CCMenuItemImage::create(s_pMenuItemStart.charMapFile, s_pMenuItemStart.charMapFilePress, this, menu_selector(StartScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pMenuItem->setPosition(ccp(CENTER.x, 270));
	pMenuItem->setTag(BTN_START);
	pMenu->addChild(pMenuItem);

	pMenuItem = CCMenuItemImage::create(s_pMenuItemHelp.charMapFile, s_pMenuItemHelp.charMapFilePress, this, menu_selector(StartScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pMenuItem->setPosition(ccp(CENTER.x, 130));
	pMenuItem->setTag(BTN_HELP);
	pMenu->addChild(pMenuItem);
}

void StartScene::buttonCallback(CCNode *pNode)
{
	if (!g_Control.isInit || !isTouchEnable)
	{
		return;
	}
	
	g_Control.playEffect(s_effectButton);

	switch (pNode->getTag())
	{
	case BTN_START:
	{
		isTouchEnable = false;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}
		break;
	case BTN_HELP:
		CCDirector::sharedDirector()->replaceScene(HelpScene::create());
		break;
	case BTN_CLOSE:
		exit();
		break;	
	case BTN_MARKET:
		CCDirector::sharedDirector()->replaceScene(MarketScene::create());
		break;
	case BTN_SOUND:
		g_Control.m_bSound = !g_Control.m_bSound;
		if (g_Control.m_bSound)
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
		break;
	default:
		break;
	}
}

void StartScene::exit(void)
{
	g_Control.save();

	SimpleAudioEngine::sharedEngine()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void StartScene::initResources(float t)
{
	g_Control.initResource();

	char szFileName[32] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < MonsterImgs.monster_idle.m_frameCount; k++)
		{
			sprintf(szFileName, MonsterImgs.monster_idle.m_strPath.c_str(), i, k);
			CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
			sprintf(szFileName, MonsterImgs.monster_defy.m_strPath.c_str(), i, k);
			CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
		}
	}

	for (int i = 1; i <= 5;i++)
	{
		for (int k = 0; k < HeroImages.hero_speed.m_frameCount; k++)
		{
			sprintf(szFileName, HeroImages.hero_speed.m_strPath.c_str(), i, k);
			CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
		}
	}

	for (int k = 0; k < HeroImages.hero_hit.m_frameCount; k++)
	{
		sprintf(szFileName, HeroImages.hero_hit.m_strPath.c_str(), k);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
		sprintf(szFileName, HeroImages.hero_hit.m_strPath.c_str(), k);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
	}

	for (int i = 0; i < CARD_COUNT; i++)
	{
		sprintf(szFileName, s_pathCard.charMapFile, i);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
		sprintf(szFileName, s_pathCard.charMapFilePress, i);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
		sprintf(szFileName, s_pathCardDisable, i);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
	}
	
	CCTextureCache::sharedTextureCache()->addImageAsync(s_pBgQuestion.m_strPath, NULL, NULL);
	CCTextureCache::sharedTextureCache()->addImageAsync(s_pBgQuestion.m_strPath, NULL, NULL);
	CCTextureCache::sharedTextureCache()->addImageAsync(s_pPathProgressEmpy, NULL, NULL);
	CCTextureCache::sharedTextureCache()->addImageAsync(s_pPathProgressFull, NULL, NULL);

	SimpleAudioEngine::sharedEngine()->preloadEffect(s_effectAnswer);
	SimpleAudioEngine::sharedEngine()->preloadEffect(s_effectEat);
	SimpleAudioEngine::sharedEngine()->preloadEffect(s_effectHit);
	SimpleAudioEngine::sharedEngine()->preloadEffect(s_effectUseItem);

	for (int k = 0; k < s_pGamePass.m_frameCount; k++)
	{
		char szFileName[32] = { 0 };
		sprintf(szFileName, s_pGamePass.m_strPath.c_str(), k);
		CCTextureCache::sharedTextureCache()->addImageAsync(szFileName, NULL, NULL);
	}

	//updateProgress(100);
	g_Control.isInit = true;
	CCLog("init_____________over");
}

void StartScene::initProgress()
{
	if (g_Control.isInit)
	{
		return;
	}

	CCLayerColor *layer = CCLayerColor::create(ccc4(25, 25, 25, 125));
	this->addChild(layer, TAG_PROGRESS, TAG_PROGRESS);

	//½ø¶È±³¾°
	CCSprite *sprite = CCSprite::create(s_pLoadProgressBg);
	sprite->setPosition(CENTER);
	addChild(sprite, TAG_PROGRESS, TAG_PROGRESS);

	progress = CCProgressTimer::create(CCSprite::create(s_pLoadProgressFull));
	progress->setType(kCCProgressTimerTypeBar);
	progress->setMidpoint(ccp(0, 0));
	progress->setBarChangeRate(ccp(1, 0));
	addChild(progress, TAG_PROGRESS, TAG_PROGRESS);
	progress->setPosition(CENTER);
}

void StartScene::loadComplete()
{
	removeChildByTag(TAG_PROGRESS, true);
	removeChildByTag(TAG_PROGRESS, true);
	removeChildByTag(TAG_PROGRESS, true);
}

void StartScene::updateProgress(int pre)
{
	CCProgressTo *to = CCProgressTo::create(1.0f, pre);
	progress->runAction(CCSequence::create(to, CCCallFunc::create(this, callfunc_selector(StartScene::loadComplete)), NULL));
}
