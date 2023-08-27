#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

USING_NS_CC;

class Projectile : public Sprite
{
public:
	static Projectile* createProjectile(std::string imgPath, std::string destroyEfName);
	virtual bool init(std::string imgPath, std::string destroyEfName);

	void launch(Vec2 direction);
	void destroy();

protected:
	virtual void update(float dt);
	bool onContactBegin(const PhysicsContact& contact);
	bool initBody();

protected:
	CC_SYNTHESIZE(int, _atk, ATK);
	CC_SYNTHESIZE(float, _spd, SPD);
	CC_SYNTHESIZE(float, _timeLife, TimeLife);

	bool _isContact = false;
	float _cooldownTime;
	Vec2 _shootDirection;
	Animate* _destroyEffect;
};

#endif // !__PROJECTILE_H__
