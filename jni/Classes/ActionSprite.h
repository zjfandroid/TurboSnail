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

	void idle();//�ȴ�
	void defy();//����
	void hit();//ײ��
	void speedup();//����

	virtual void update(float delta);

	//����,ÿ��״̬Ҫִ�еĶ���
	CC_SYNTHESIZE_RETAIN(CCAction*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(CCAction*, _defyAction, DefyAction);
	CC_SYNTHESIZE_RETAIN(CCAction*, _hitAction, HitAction); 
	CC_SYNTHESIZE_RETAIN(CCAction*, _speedUpAction, SpeedUpAction);

	//״̬,���澫��ĵ�ǰ����/״̬
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//����
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(float, _damage, Damage);

};

#endif