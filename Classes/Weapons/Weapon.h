#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "Projectiles/Projectile.h"

USING_NS_CC;

class Weapon : public Node
{
public:
	static Weapon* createWeapon(Sprite* model, Vec2 shootPoint);
	virtual bool init(Sprite* model, Vec2 shootPoint);
protected:
	CC_SYNTHESIZE(Sprite*, _model, Model);
	CC_SYNTHESIZE(Vec2, _shootPoint, ShootPoint);
protected:
	CC_SYNTHESIZE(float, _atk, ATK);
	CC_SYNTHESIZE(float, _aspd, ASPD);
	CC_SYNTHESIZE(std::vector<Projectile*>, _projectiles, WP_Projectiles);
protected:
	float _cooldownTime;
protected:
	void onMouseDown(cocos2d::EventMouse* event);
	void attack(Vec2 direction);
	virtual void update(float dt);
};


#endif // !__WEAPON_H__
