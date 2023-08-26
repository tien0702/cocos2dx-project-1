#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class InputManager : public Node
{
public:
	static InputManager* getInstance();

	void AddKey(EventKeyboard::KeyCode key);
	bool GetKey(EventKeyboard::KeyCode key);

	Vec2 inputDirection();
	Vec2 mousePosition();
protected:
	std::map<EventKeyboard::KeyCode, bool> _keyUsed;
	CC_SYNTHESIZE(float, _horizontal, Horizontal);
	CC_SYNTHESIZE(float, _vertical, Vertical);

	CC_SYNTHESIZE(Camera*, _targetCam, TargetCam);
	Vec2 _mousePosition, _tempMousePos;
	Vec2 _visibleSize;
protected:
	bool init();
	static InputManager* _instance;

	void onKeyPress(EventKeyboard::KeyCode key, Event* ev);
	void onKeyReleased(EventKeyboard::KeyCode key, Event* ev);

	void onMouseMove(cocos2d::EventMouse* event);

	void update(float dt);
	void onEnter();
	void onExit();
};

#endif // !__INPUT_MANAGER_H__
