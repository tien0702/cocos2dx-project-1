#ifndef __SWALLOW_TOUCH_LAYER_H__
#define __SWALLOW_TOUCH_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class SwallowTouchLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(SwallowTouchLayer);
protected:
	bool onTouchBegan(Touch* touch, Event* event);
};

#endif // !__SWALLOW_TOUCH_LAYER_H__
