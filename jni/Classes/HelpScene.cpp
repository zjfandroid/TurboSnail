#include "GameControl.h"

USING_NS_CC;

HelpScene::HelpScene()
{
}

HelpScene::~HelpScene()
{
}

bool HelpScene::init()
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

void HelpScene::update(float delta)
{
}

void HelpScene::initBackground()
{
	CCSprite *bg = CCSprite::create(s_pBgMain);
	bg->setPosition(CENTER);
	addChild(bg);

	bg = CCSprite::create(s_pBgHelpBoard);
	bg->setPosition(CENTER);
	addChild(bg);

	char ch[32] = { 0 };
	sprintf(ch, help_anim.m_strPath.c_str(), 0);
	bg = CCSprite::create(ch);
	bg->setPosition(help_anim.m_Position);

	CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(help_anim);
	bg->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(bg);
}

void HelpScene::initButton()
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(s_pMenuItemBack.charMapFile, s_pMenuItemBack.charMapFilePress, this, menu_selector(HelpScene::buttonCallback));
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

	pMenuItem = CCMenuItemImage::create(s_pMenuItemHelpStart.charMapFile, s_pMenuItemHelpStart.charMapFilePress, this, menu_selector(HelpScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pMenuItem->setPosition(ccp(CENTER.x, 116));
	pMenuItem->setTag(BTN_START);
	pMenu->addChild(pMenuItem);
}

void HelpScene::buttonCallback(CCNode *pNode)
{
	CCLog("          call back  = %d  ", pNode->getTag());
	switch (pNode->getTag())
	{
	case BTN_START:
	{
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}
		break;
	case BTN_CLOSE:
		CCDirector::sharedDirector()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}
}