#include "GameControl.h"

USING_NS_CC;

MarketScene::MarketScene():
selectedIndex(0)
{
}

MarketScene::~MarketScene()
{
}

bool MarketScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		initBackground();
		initLabelAtlas();
		initButton();
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void MarketScene::update(float delta)
{
}

void MarketScene::initBackground()
{
	CCSprite *bg = CCSprite::create(s_pBgMain);
	bg->setPosition(CENTER);
	addChild(bg);

	bg = CCSprite::create(s_pBgMarketBoard);
	bg->setPosition(CENTER);
	addChild(bg);
}

void MarketScene::initButton()
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(s_pMenuItemBack.charMapFile, s_pMenuItemBack.charMapFilePress, this, menu_selector(MarketScene::buttonCallback));
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
		pMenu->setTag(TAG_MENU);
	}

	pMenuItem = CCMenuItemImage::create(s_pMenuItemBuy.charMapFile, s_pMenuItemBuy.charMapFilePress, s_pBuyDisable, this, menu_selector(MarketScene::buttonCallback));
	pMenuItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pMenuItem->setPosition(ccp(CENTER.x, 120));
	pMenuItem->setTag(BTN_BUY);
	pMenu->addChild(pMenuItem);

	char szFileName[32] = { 0 };
	char szFileName2[32] = { 0 };
	char szFileName3[32] = { 0 };
	for (int i = 0; i < CARD_COUNT; i++)
	{
		sprintf(szFileName, s_pathCard.charMapFile, i);
		sprintf(szFileName2, s_pathCard.charMapFilePress, i);
		sprintf(szFileName3, s_pathCardDisable, i);

		CCMenuItemImage *pItem0 = CCMenuItemImage::create(szFileName, szFileName2, szFileName3);
		CCMenuItemImage *pItem1 = CCMenuItemImage::create(szFileName2, szFileName);
		CCMenuItemToggle *pToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(MarketScene::buttonCallback), pItem0, pItem1, NULL);
		pToggle->setPosition(ccp(120 * i + s_pathCard.m_Position.x, s_pathCard.m_Position.y));
		pToggle->setTag(BTN_CARD + i);

		if (g_Control.cards[i] > 0)
		{
			CCSprite *sprite = CCSprite::create(s_pathCardbuy.m_strPath);
			sprite->setPosition(s_pathCardbuy.m_Position);
			pToggle->addChild(sprite, TAG_CARD_BUY, TAG_CARD_BUY);
		}

		pMenu->addChild(pToggle);
	}
	checkCard(BTN_CARD);
}

void MarketScene::buttonCallback(CCNode *pNode)
{
	switch (pNode->getTag())
	{
	case BTN_BUY:
		buyCard(pNode);
		break;
	case BTN_CLOSE:
		CCDirector::sharedDirector()->replaceScene(StartScene::create());
		break;
	default:
		checkCard(pNode->getTag());
		break;
	}
}

void MarketScene::initLabelAtlas()
{
	CCSprite *sprite = CCSprite::create(s_pathMarketTomato.m_strPath);
	sprite->setPosition(s_pathMarketTomato.m_Position);
	addChild(sprite);

	CCLabelAtlas *pTextLabel = g_Control.creatLabelAtlas(g_Control.m_nCoin, s_pNumMarketCoin, this, LabelAtlas_COIN);
	pTextLabel->setPosition(s_pNumMarketCoin.m_Position);

	pTextLabel = g_Control.creatLabelAtlas(PRICE_CHANGE_QUESTION, s_pNumMarketCoin, this, LabelAtlas_PRICE);
	pTextLabel->setPosition(ccp(s_pNumMarketCoin.m_Position.x, s_pNumMarketCoin.m_Position.y - 260));
}

void MarketScene::checkCard(int index)
{
	CCMenu *pMenu = (CCMenu *)this->getChildByTag(TAG_MENU);

	char szFileName[32] = { 0 };
	for (int i = 0; i < CARD_COUNT; i++)
	{
		int tag = BTN_CARD + i;
		CCMenuItemToggle *pToggle = (CCMenuItemToggle *)pMenu->getChildByTag(tag);

		if (tag == index)
		{
			selectedIndex = index;
			pToggle->setSelectedIndex(1);
			pToggle->setEnabled(false);
			sprintf(szFileName, s_pathCardInfo.m_strPath, i);

			int price = getPrice(tag);
			updateLabelAtlas(price, LabelAtlas_PRICE);

			CCMenuItemImage *pMenuItem = (CCMenuItemImage *)pMenu->getChildByTag(BTN_BUY);
			if (g_Control.cards[i] <= 0 && g_Control.m_nCoin > price)
			{
				pMenuItem->setEnabled(true);
			}
			else
			{
				pMenuItem->setEnabled(false);
			}
		}
		else
		{
			pToggle->setSelectedIndex(0);
			pToggle->setEnabled(true);
		}
	}

	this->removeChildByTag(CARD_INFO);
	CCSprite *pcdSprite = CCSprite::create(szFileName);
	pcdSprite->setPosition(s_pathCardInfo.m_Position);
	pcdSprite->setTag(CARD_INFO);
	this->addChild(pcdSprite);
	pcdSprite->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.2f, 1.0f), CCFadeTo::create(0.2f, 255), NULL), NULL));
}

void MarketScene::updateLabelAtlas(int num, int tag)
{
	char txt[32] = { 0 };
	sprintf(txt, "%d", num);
	CCLabelAtlas *label = (CCLabelAtlas *)getChildByTag(tag);
	label->setString(txt);
}

int MarketScene::getPrice(int tag)
{
	int price = 0;
	switch (tag)
	{
	case BTN_CARD://»»Ìâ¿¨
		price = PRICE_CHANGE_QUESTION;
		break;
	case BTN_CARD + 1://ÅÅ³ý¿¨
		price = PRICE_EXCLUDE_ANSWER;
		break;
	case BTN_CARD + 2://Ãâ´ð¿¨
		price = PRICE_NO_ANSWER;
		break;
	case BTN_CARD + 3://¼ÓËÙ¿¨
		price = PRICE_SPEED_UP;
		break;
	case BTN_CARD + 4://´ð°¸¿¨
		price = PRICE_RIGHT_ANSWER;
		break;
	case BTN_CARD + 5://·­±¶¿¨
		price = PRICE_DOUBLE_SCORE;
		break;
	default:
		break;
	}

	return price;
}

void MarketScene::buyCard(CCNode * pNode)
{
	int price = getPrice(selectedIndex);
	if (g_Control.m_nCoin >= price)
	{
		CCMenuItemImage *pItem = (CCMenuItemImage *)pNode;
		pItem->setEnabled(false);

		//¹´Ñ¡ÒÑÂòÏî
		CCMenu *pMenu = (CCMenu *)this->getChildByTag(TAG_MENU);
		CCMenuItemToggle *pToggle = (CCMenuItemToggle *)pMenu->getChildByTag(selectedIndex);
		CCSprite *sprite = CCSprite::create(s_pathCardbuy.m_strPath);
		sprite->setPosition(s_pathCardbuy.m_Position);
		pToggle->addChild(sprite, TAG_CARD_BUY, TAG_CARD_BUY);

		//¿ÛÇ®
		g_Control.m_nCoin -= price;
		updateLabelAtlas(g_Control.m_nCoin, LabelAtlas_COIN);

		g_Control.cards[selectedIndex - BTN_CARD] = 1;
		g_Control.save();
	}
}
