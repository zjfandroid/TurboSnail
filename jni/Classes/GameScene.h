#ifndef  _GAME_SCENE_H_
#define  _GAME_SCENE_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::CCScene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

	CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);

	virtual void update(float delta);
};
#endif
