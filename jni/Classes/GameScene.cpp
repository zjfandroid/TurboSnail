#include "GameControl.h"

USING_NS_CC;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer, 0);
		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 1);

		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void GameScene::update(float delta)
{
	if (g_Control.gameState != GRS_OVER)
	{
		_hudLayer->update(delta);
		_gameLayer->update(delta);
	}
}
