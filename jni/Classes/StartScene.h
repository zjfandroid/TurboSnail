#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public cocos2d::CCScene
{
public:
	enum TAG
	{
		BTN_CLOSE = 200,
		BTN_HELP,
		BTN_START,
		BTN_MARKET,
		BTN_SOUND,
	};

public:
	StartScene();
	~StartScene();

	virtual bool init();
	CREATE_FUNC(StartScene);

	virtual void update(float delta);
	void initBackground();
	void initButton();
	void buttonCallback(CCNode *pNode);
	void exit(void);
};

#endif