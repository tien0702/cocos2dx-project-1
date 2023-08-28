#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "cocos2d.h"
#include "Entities/Health.h"

USING_NS_CC;

class HealthBar : public Sprite
{
public:
	static HealthBar* create(std::string borderPath, std::string fillPath);
	virtual bool init(std::string borderPath, std::string fillPath);

	virtual void setHealthTarget(Health* healthTarget);
	virtual Health* getHealthTarget() { return _healthTarget; }
protected:
	virtual void onEnter();
	virtual void onExit();
	virtual void onHPChange(int val);

protected:
	Health* _healthTarget;

	Sprite* _border, * _fill;
};

#endif // !__HEALTH_BAR_H__
