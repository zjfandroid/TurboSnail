#include "GameControl.h"

HudLayer::HudLayer()
{
}

HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		this->initBackground();

		bRet = true;
	} while (0);

	return bRet;
}

void HudLayer::initBackground()
{
	Res *p = (Res*)g_Control.m_Resource["HudLayer"];
	if (NULL == p)
	{
		return;
	}

	m_skySprite = CMImage::create(&(p->m_skyBackGround), this, ORDER_BG, TAG_BG_FAR_LAYER, CCPointZero);
	m_skySpriteRe = CMImage::create(&(p->m_skyBackGround), this, ORDER_BG, TAG_BG_FAR_LAYER, CCPointZero);
	m_midSprite = CMImage::create(&(p->m_landscape), this, ORDER_BG, TAG_BG_MID_LAYER, CCPointZero);
	m_midSpriteRe = CMImage::create(&(p->m_landscape), this, ORDER_BG, TAG_BG_MID_LAYER, CCPointZero);
	m_roadSprite = CMImage::create(&(p->m_roadBackGround), this, ORDER_BG, TAG_BG_NEAR_LAYER, CCPointZero);
	m_roadSpriteRe = CMImage::create(&(p->m_roadBackGround), this, ORDER_BG, TAG_BG_NEAR_LAYER, CCPointZero);

	m_fSkyWidth = m_skySprite->getContentSize().width;
	m_fMidWidth = m_midSprite->getContentSize().width;
	m_fRoadWidth = m_roadSprite->getContentSize().width;

	m_skySpriteRe->setPosition(ccp(m_fSkyWidth, m_skySpriteRe->getPosition().y));
	m_midSpriteRe->setPosition(ccp(m_fMidWidth, m_midSpriteRe->getPosition().y));
	m_roadSpriteRe->setPosition(ccp(m_fRoadWidth, m_roadSprite->getPosition().y));

}

void HudLayer::update(float dt)
{
	CCArray *bgSprites = this->getChildren();
	CCObject *obj = NULL;

	CCARRAY_FOREACH(bgSprites, obj)
	{
		movingBackground(obj, dt);
	}
}

void HudLayer::movingBackground(CCObject * obj, float dt)
{
	CCNode *bgNode = (CCNode*)obj;
	int tag = bgNode->getTag();
	
	if (tag == TAG_BG_NEAR_LAYER)
	{
		bgNode->setPositionX(bgNode->getPositionX() + g_Control.getRoadVelocity() * dt);
		if (bgNode->getPositionX() < -m_fRoadWidth)
		{
			//-2的目的是为了避免背景之间有可能因为加载产生的黑线
			bgNode->setPositionX(bgNode->getPositionX() + m_fRoadWidth * 2 - 2);
		}
	}
	else if (tag == TAG_BG_MID_LAYER)
	{
		bgNode->setPositionX(bgNode->getPositionX() + g_Control.getMidVelocity() * dt);
		if (bgNode->getPositionX() < -m_fMidWidth)
		{
			bgNode->setPositionX(bgNode->getPositionX() + m_fMidWidth * 2 - 2);
		}
	}
	else if (tag == TAG_BG_FAR_LAYER)
	{
		bgNode->setPositionX(bgNode->getPositionX() + g_Control.getSkyVelocity() * dt);
		if (bgNode->getPositionX() < -m_fSkyWidth)
		{
			bgNode->setPositionX(bgNode->getPositionX() + m_fSkyWidth * 2 - 2);
		}
	}
}
