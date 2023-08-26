#ifndef __ENEMY_CONTROLLER_H__
#define __ENEMY_CONTROLLER_H__

#include "EntityController.h"
#include "DamageSystem/IDamageable.h"

class EnemyController : public EntityController, public IDamageable
{
public:
	static EnemyController* create(std::string entityName);

	virtual bool init(std::string entityName);

	virtual void takeDamage(int damage);
protected:
	bool initComponents();
	bool initAnimation();
	bool initBody();

};

#endif // !__ENEMY_CONTROLLER_H__
