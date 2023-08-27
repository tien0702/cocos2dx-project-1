#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class EffectManager
{
public:
	static EffectManager* getInstance();

	bool loadEffects();

	Animate* getEffect(std::string name);
};

#endif // !__EFFECT_MANAGER_H__
