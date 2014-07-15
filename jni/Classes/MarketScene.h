#ifndef  _MARKET_SCENE_H_
#define  _MARKET_SCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class MarketScene : public cocos2d::CCScene
{
public:
	enum Price
	{
		PRICE_CHANGE_QUESTION = 10,
		PRICE_EXCLUDE_ANSWER = 20,
		PRICE_NO_ANSWER = 50,
		PRICE_SPEED_UP = 100,
		PRICE_RIGHT_ANSWER = 180,
		PRICE_DOUBLE_SCORE = 250,
	};

public:
	MarketScene();
	~MarketScene();

	virtual bool init();
	CREATE_FUNC(MarketScene);

	virtual void update(float delta);
	void initBackground();
	void initButton();
	void initLabelAtlas();

	void buttonCallback(CCNode *pNode);
	void checkCard(int index);
	void updateLabelAtlas(int num, int tag);
	int getPrice(int tag);
	void buyCard(CCNode * pNode);

private:
	int selectedIndex;
};
#endif