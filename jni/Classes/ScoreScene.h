#ifndef _SCORE_SCENE_H_
#define _SCORE_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class ScoreScene : public cocos2d::CCScene
{
public:
	enum TAG
	{
		BTN_CLOSE = 200,
		BTN_CHART,
		BTN_RESTART,

		Label_SCORE_HIGHTEST,
		Label_RANK,
	};

public:
	ScoreScene();
	~ScoreScene();

	virtual bool init();
	CREATE_FUNC(ScoreScene);

	virtual void update(float delta);
	void initBackground();
	void initButton();
	void buttonCallback(CCNode *pNode);
	void initLabelAtlas();
};

#endif