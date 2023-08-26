#ifndef __CHARACTER_CONTROLLER_H__
#define __CHARACTER_CONTROLLER_H__

#include "EntityController.h"
#include "DamageSystem/IDamageable.h"
#include "Weapons/Weapon.h"

class CharacterController : public EntityController, public IDamageable
{
public:
	static CharacterController* create(std::string entityName);
	virtual bool init(std::string entityName);
	virtual void takeDamage(int damage);

	void equip(Weapon* weapon);
	virtual void move(Vec2 direction, float deltaTime);
protected:
	Node* _weaponAttachment;
	Weapon* _weapon;
protected:
	virtual void update(float dt);
	virtual void onEnter();
	virtual void onExit();
protected:
	bool initComponents();
	bool initAnimation();
	bool initBody();
	void weaponLookAtMouse();
	void lookAtMouse();
};

#endif // !__CHARACTER_CONTROLLER_H__
