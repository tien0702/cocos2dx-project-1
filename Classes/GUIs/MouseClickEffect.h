#ifndef __TOUCH_EFFECT_H__
#define __TOUCH_EFFECT_H__

#include "cocos2d.h"

USING_NS_CC;

class MouseClickEffect : public Sprite
{
public:
	static MouseClickEffect* createEffect(std::string efName);
	virtual bool init(std::string efName);

protected:
	void onMouseDown(EventMouse* ev);
	Animate* _effect;
};

#endif // !__TOUCH_EFFECT_H__
