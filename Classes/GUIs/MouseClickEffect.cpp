#include "MouseClickEffect.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Utilities.h"
#include "Managers/InputManager.h"

MouseClickEffect* MouseClickEffect::createEffect(std::string efName)
{
	auto newTarget = new MouseClickEffect();
	if (newTarget && newTarget->init(efName))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool MouseClickEffect::init(std::string efName)
{
	if (!Sprite::init())
	{
		log("init MouseClickEffect failed!");
		return false;
	}

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(DefaultPath::EFFECT_PATH + efName + ".plist", 
		DefaultPath::EFFECT_PATH + efName + ".png");

	auto ani = Utilities::createAnimation(efName);
	this->initWithSpriteFrame(ani.first->getFrames().at(0)->getSpriteFrame());
	_effect = Animate::create(ani.first);
	_effect->retain();

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(MouseClickEffect::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void MouseClickEffect::onMouseDown(EventMouse* ev)
{
	int tag = 1;
	this->setPosition(InputManager::getInstance()->mousePosition());
	this->stopActionByTag(tag);

	auto effectClone = _effect->clone();
	effectClone->setTag(tag);
	this->runAction(effectClone);
}
