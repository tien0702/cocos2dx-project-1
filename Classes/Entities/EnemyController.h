#ifndef __ENEMY_CONTROLLER_H__
#define __ENEMY_CONTROLLER_H__

#include "EntityController.h"
#include "GUIs/HealthBar.h"

class EnemyController : public EntityController
{
public:
	static EnemyController* create(std::string entityName);

	virtual bool init(std::string entityName);

	virtual void takeDamage(int damage);
protected:
	bool initComponents();
	bool initAnimation();
	bool initBody();

	virtual void update(float dt);

	virtual void onEnter();
	virtual void onExit();
protected:
	HealthBar* _healthBar;
};

#endif // !__ENEMY_CONTROLLER_H__
