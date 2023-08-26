#ifndef __BASE_BUTTON_H__
#define __BASE_BUTTON_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class BaseButton : public ui::Button
{
public:
	virtual bool init();
	CREATE_FUNC(BaseButton);
protected:
	void onButtonPressed(Ref* sender, ui::Widget::TouchEventType eventType);
};

#endif // !__BASE_BUTTON_H__
