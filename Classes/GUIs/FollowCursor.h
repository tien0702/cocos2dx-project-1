#ifndef __CUSTOM_CURSOR_H__
#define __CUSTOM_CURSOR_H__

#include "cocos2d.h"

USING_NS_CC;

class FollowCursor : public Sprite
{
public:
	static FollowCursor* getInstance();
	void setVisibleCursor(bool visible);
protected:
	static FollowCursor* _instance;
	virtual bool init();

protected:
	virtual void onEnter();
	virtual void update(float dt);
	virtual void onExit();
};

#endif // !__CUSTOM_CURSOR_H__
