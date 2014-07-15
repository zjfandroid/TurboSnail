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
		initBackground();
		initButton();
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void StartScene::update(float delta)
{
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
	CCLog("          call back  = %d  ", pNode->getTag());
	switch (pNode->getTag())
	{
	case BTN_START:
	{
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