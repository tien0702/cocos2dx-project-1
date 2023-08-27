#ifndef __ENTITY_CONTROLLER_H__
#define __ENTITY_CONTROLLER_H__

#include "cocos2d.h"
#include "Health.h"
#include "DamageSystem/IDamageable.h"

USING_NS_CC;

class EntityController : public Node, public IDamageable
{
public:
	enum EntityState { Idle, Move, Attack, Hurt, Die };
	virtual bool init();
	CREATE_FUNC(EntityController);
	virtual void takeDamage(int amount);
protected:
	void move(Vec2 direction, float deltaTime);
protected:
	Sprite* _model;
protected:
	CC_SYNTHESIZE(float, _atk, ATK);
	CC_SYNTHESIZE(float, _hp, HP);
	CC_SYNTHESIZE(float, _spd, SPD);
	CC_SYNTHESIZE(float, _aspd, ASPD);
	CC_SYNTHESIZE(EntityState, _state, State);
	CC_SYNTHESIZE(std::string, _entityName, EntityName);

	Health* _health;

	virtual void onEnter();
	virtual void onExit();
};

#endif // !__ENTITY_CONTROLLER_H__	
