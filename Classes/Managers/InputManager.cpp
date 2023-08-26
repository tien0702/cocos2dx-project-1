#include "InputManager.h"

InputManager* InputManager::_instance;

InputManager* InputManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new InputManager();
		_instance->init();
	}

	return _instance;
}

void InputManager::AddKey(EventKeyboard::KeyCode key)
{
	if (_keyUsed.find(key) == _keyUsed.end())
	{
		_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(key, false));
	}
}

bool InputManager::GetKey(EventKeyboard::KeyCode key)
{
	if (_keyUsed.find(key) == _keyUsed.end())
	{
		log("Key does not exist!");
		return false;
	}
	return _keyUsed[key];
}

Vec2 InputManager::inputDirection()
{
	return Vec2(_horizontal, _vertical);
}

bool InputManager::init()
{
	if (!Node::init()) {
		log("init input failed!");
		return false;
	}

	// Load default keys
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_W, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_UP_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_S, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_DOWN_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_D, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_A, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_LEFT_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_SPACE, false));

	// Set default value
	_horizontal = 0;
	_vertical = 0;
	_visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
	_targetCam = Director::getInstance()->getRunningScene()->getDefaultCamera();


	// Add event
	auto eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	eventListenerKeyboard->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPress, this);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(eventListenerKeyboard, this);

	auto listener = cocos2d::EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	_instance->retain();
	return true;
}

Vec2 InputManager::mousePosition()
{
	return _mousePosition;
}

void InputManager::onKeyPress(EventKeyboard::KeyCode key, Event* ev)
{
	if (_keyUsed.find(key) == _keyUsed.end())
		return;
	_keyUsed[key] = true;

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_vertical = 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_vertical = -1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_horizontal = 1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_horizontal = -1;
		break;
	default:
		break;
	}
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode key, Event* ev)
{
	if (_keyUsed.find(key) == _keyUsed.end())
		return;
	_keyUsed[key] = false;

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_S] || _keyUsed[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
			_vertical = -1;
		else
			_vertical = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_W] || _keyUsed[EventKeyboard::KeyCode::KEY_UP_ARROW])
			_vertical = 1;
		else _vertical = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_A] || _keyUsed[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
			_horizontal = -1;
		else _horizontal = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_D] || _keyUsed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
			_horizontal = 1;
		else _horizontal = 0;
		break;
	default:
		break;
	}
}

void InputManager::onMouseMove(cocos2d::EventMouse* event)
{
	_tempMousePos = event->getLocation();
	_tempMousePos.y = _visibleSize.y - _tempMousePos.y;
}

void InputManager::update(float dt)
{
	_mousePosition = (_targetCam->getPosition() - _visibleSize / 2) + _tempMousePos;
}

void InputManager::onEnter()
{
	Node::onEnter();
	this->scheduleUpdate();
}

void InputManager::onExit()
{
	Node::onExit();
}
