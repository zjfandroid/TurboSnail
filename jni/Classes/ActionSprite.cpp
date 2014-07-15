#include "ActionSprite.h"

ActionSprite::ActionSprite()
{
	_idleAction = NULL;
	_defyAction = NULL;
	_hitAction = NULL;
	_speedUpAction = NULL;
}

ActionSprite::~ActionSprite()
{

}

void ActionSprite::update(float delta)
{

}

void ActionSprite::idle()
{
	this->stopAllActions();
	this->runAction(_idleAction);
	_actionState = kActionStateIdle;
}

void ActionSprite::defy()
{
	if (kActionStateDefy != _actionState)
	{
		this->stopAllActions();
		this->runAction(_defyAction);
		_actionState = kActionStateDefy;
	}
}

void ActionSprite::hit()
{
	if (kActionStateHit != _actionState)
	{
		this->stopAllActions();
		this->runAction(_hitAction);
		_actionState = kActionStateHit;
	}
}

void ActionSprite::speedup()
{
	if (kActionStateSpeedUp != _actionState)
	{
		this->stopAllActions();
		this->runAction(_speedUpAction);
		_actionState = kActionStateSpeedUp;
	}
}

