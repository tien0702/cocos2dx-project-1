#ifndef __ENEMY_CONTROLLER_H__
#define __ENEMY_CONTROLLER_H__

#include "EntityController.h"
#include "Weapons/Weapon.h"
#include "GUIs/HealthBar.h"

class EnemyController : public EntityController
{
public:
	static EnemyController* create(std::string entityName);
	std::vector<function<void(EnemyController*)>> _onDie;

	virtual bool init(std::string entityName);

	virtual void takeDamage(int damage);
protected:
	bool initComponents();
	bool initAnimation();
	bool initBody();

	virtual void update(float dt);

	virtual void onEnter();
	virtual void onExit();
	bool onContactBegin(const PhysicsContact& contact);

	void destroy();
protected:
	HealthBar* _healthBar;
	Animate* _destroyEffect;

	float _hurtDelay = 0.5f;
	float _cooldownHurtDelay;

	CC_SYNTHESIZE(int, _level, Level);
};

#endif // !__ENEMY_CONTROLLER_H__
