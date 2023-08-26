#include "FollowCursor.h"
#include "Managers/InputManager.h"

FollowCursor* FollowCursor::_instance;

FollowCursor* FollowCursor::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new FollowCursor();
        _instance->init();
        _instance->retain();
    }

    return _instance;
}

bool FollowCursor::init()
{
    if (!Sprite::init())
    {
        log("init FollowCursor failed!");
        return false;
    }

    return true;
}

void FollowCursor::setVisibleCursor(bool visible)
{
    Director::getInstance()->getOpenGLView()->setCursorVisible(visible);
}

void FollowCursor::update(float dt)
{
    this->setPosition(InputManager::getInstance()->mousePosition());
    //log("%lf | %lf", InputManager::getInstance()->mousePosition().x, InputManager::getInstance()->mousePosition().y);
}

void FollowCursor::onEnter()
{
    Sprite::onEnter();
    this->scheduleUpdate();
}

void FollowCursor::onExit()
{
    Sprite::onExit();
}
