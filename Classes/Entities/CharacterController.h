#ifndef __CHARACTER_CONTROLLER_H__
#define __CHARACTER_CONTROLLER_H__

#include "EntityController.h"
#include "Weapons/Weapon.h"
#include "GUIs/HealthBar.h"

class CharacterController : public EntityController
{
public:
	static CharacterController* create(std::string entityName);
	virtual bool init(std::string entityName);
	virtual void takeDamage(int damage);

	void equip(Weapon* weapon);
	virtual void move(Vec2 direction, float deltaTime);
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
protected:
	Node* _weaponAttachment;
	Weapon* _weapon;
	HealthBar* _healthBar;
};

#endif // !__CHARACTER_CONTROLLER_H__
