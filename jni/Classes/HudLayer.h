#ifndef _HUDLAYER_H
#define _HUDLAYER_H

#include "cocos2d.h"
#include "CMImage.h"

USING_NS_CC; 
using namespace std;

class HudLayer : public cocos2d::CCLayer
{
public:
	struct Res
	{
		CMImage::ImageData m_skyBackGround;
		CMImage::ImageData m_landscape;
		CMImage::ImageData m_roadBackGround;
	};

public:
	enum TAG_BG
	{
		TAG_BG_NEAR_LAYER,
		TAG_BG_MID_LAYER,
		TAG_BG_FAR_LAYER,
	};

	enum Z_ORDER
	{
		ORDER_BG,
	};

public:
	HudLayer();
	~HudLayer();

	bool init();
	void initBackground();
	CREATE_FUNC(HudLayer);

	virtual void update(float dt);
	void movingBackground(CCObject * obj, float dt);

private:
	//Ô¶¾°²ã
	CCSprite *m_skySprite;
	CCSprite *m_skySpriteRe;
	float m_fSkyWidth;

	//ÖÐ¾°²ã
	CCSprite *m_midSprite;
	CCSprite *m_midSpriteRe;
	float m_fMidWidth;
	
	//½ü¾°²ã
	CCSprite *m_roadSprite;
	CCSprite *m_roadSpriteRe;
	float m_fRoadWidth;
};

#endif