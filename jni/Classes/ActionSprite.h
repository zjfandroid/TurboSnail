#ifndef ACTION_SPRITE_H
#define ACTION_SPRITE_H
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;

class ActionSprite : public cocos2d::CCSprite
{
public:
	ActionSprite();
	~ActionSprite();

	void idle();//等待
	void defy();//挑衅
	void hit();//撞击
	void speedup();//加速

	virtual void update(float delta);

	//动作,每种状态要执行的动作
	CC_SYNTHESIZE_RETAIN(CCAction*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(CCAction*, _defyAction, DefyAction);
	CC_SYNTHESIZE_RETAIN(CCAction*, _hitAction, HitAction); 
	CC_SYNTHESIZE_RETAIN(CCAction*, _speedUpAction, SpeedUpAction);

	//状态,保存精灵的当前动作/状态
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//属性
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(float, _damage, Damage);

};

#endif