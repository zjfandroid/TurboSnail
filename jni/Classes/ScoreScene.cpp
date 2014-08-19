#include "GameControl.h"

USING_NS_CC;

ScoreScene::ScoreScene()
{
}

ScoreScene::~ScoreScene()
{
}

bool ScoreScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		g_Control.playBGMusic(s_musicBgGameOver);

		initBackground();
		initButton();
		initLabelAtlas();
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void ScoreScene::update(float delta)
{
	CCLabelAtlas *pTextLabel = (CCLabelAtlas *)getChildByTag(Label_SCORE_HIGHTEST);
	char num[32] = { 0 };
	sprintf(num, "%d", g_Control.m_nTotalScore);
	pTextLabel->setString(num);

	pTextLabel = (CCLabelAtlas *)getChildByTag(Label_RANK);
	sprintf(num, "%d", g_Control.m_nRank);
	pTextLabel->setString(num);
}

void ScoreScene::initBackground()
{
	CCSprite *bg = CCSprite::create(s_pBgMain);
	bg->setPosition(CENTER);
	addChild(bg);

	bg = CCSprite::create(s_pBgPropBoard);
	bg->setPosition(CENTER);
	addChild(bg);
}

void ScoreScene::initButton()
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(s_pMenuItemClose.charMapFile, s_pMenuItemClose.charMapFilePress, this, menu_selector(ScoreScene::buttonCallback));
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

	//pMenuItem = CCMenuItemImage::create(s_pMenuItemChart.charMapFile, s_pMenuItemChart.charMapFilePress, this, menu_selector(ScoreScene::buttonCallback));
	//pMenuItem->setAnchorPoint(ccp(0, 1));
	//pMenuItem->setPosition(ccp(0,SCREEN.height));
	//pMenuItem->setTag(BTN_CHART);
	//pMenu->addChild(pMenuItem);

	pMenuItem = CCMenuItemImage::create(s_pMenuItemRestart.charMapFile, s_pMenuItemRestart.charMapFilePress, this, menu_selector(ScoreScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pMenuItem->setPosition(ccp(CENTER.x, 120));
	pMenuItem->setTag(BTN_RESTART);
	pMenu->addChild(pMenuItem);
}

void ScoreScene::buttonCallback(CCNode *pNode)
{
	g_Control.playEffect(s_effectButton);

	switch (pNode->getTag())
	{
	case BTN_RESTART:
	{
		g_Control.m_nScore = 0;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}
		break;
	case BTN_CHART:
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
		break;
	case BTN_CLOSE:
		CCDirector::sharedDirector()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}
}

void ScoreScene::initLabelAtlas()
{
	CCSprite *sprite = CCSprite::create(s_pathTomato.m_strPath);
	sprite->setPosition(s_pathTomato.m_Position);
	addChild(sprite);

	g_Control.creatLabelAtlas(g_Control.m_nCoin, s_pNumScoreCoin, this);
	CCLabelAtlas *pTextLabel = g_Control.creatLabelAtlas(0, s_pNumScoreYellow, this);
	char num[32] = {};
	sprintf(num, "%d:%d", g_Control.m_nRight, g_Control.m_nWrong);
	pTextLabel->setString(num);

	g_Control.creatLabelAtlas(g_Control.m_nScore, s_pNumScoreGreen, this);
	g_Control.creatLabelAtlas(g_Control.m_nTotalScore, s_pNumScoreBlue, this, Label_SCORE_HIGHTEST);

	pTextLabel = g_Control.creatLabelAtlas(g_Control.m_nRank, s_pNumScoreBlue, this, Label_RANK);
	pTextLabel->setPosition(ccp(s_pNumScoreBlue.m_Position.x, s_pNumScoreBlue.m_Position.y - 75));
}
