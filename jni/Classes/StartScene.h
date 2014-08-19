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
		TAG_PROGRESS,
	};

public:
	StartScene();
	~StartScene();

	virtual bool init();
	CREATE_FUNC(StartScene);
	void buttonCallback(CCNode *pNode);

	void initBackground();
	void initButton();
	void exit(void);
	void initResources(float t);
	void initProgress();
	void loadComplete();
	void updateProgress(int param1);

private:
	CCProgressTimer *progress;
	bool isTouchEnable;
};

#endif