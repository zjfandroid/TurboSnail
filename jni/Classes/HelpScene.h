#ifndef  _HELP_SCENE_H_
#define  _HELP_SCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class HelpScene : public cocos2d::CCScene
{
public:
	enum TAG
	{
		BTN_CLOSE = 200,
		BTN_START,
	};

public:
	HelpScene();
	~HelpScene();

	virtual bool init();
	CREATE_FUNC(HelpScene);

	virtual void update(float delta);
	void initBackground();
	void initButton();
	void buttonCallback(CCNode *pNode);
};
#endif