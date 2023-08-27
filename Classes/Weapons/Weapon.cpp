#include "Weapon.h"
#include "Managers/InputManager.h"
#include "Managers/AudioManager.h"
#include "Utilities/DefaultPath.h"

Weapon* Weapon::create(Sprite* model, Vec2 shootPoint)
{
	auto newTarget = new Weapon();
	if (newTarget && newTarget->init(model, shootPoint))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool Weapon::init(Sprite* model, Vec2 shootPoint)
{
	if (!Node::init())
	{
		log("init Weapon failed!");
		return false;
	}
	this->_model = model;
	this->_shootPoint = shootPoint;
	_cooldownTime = 0;

	_glowEf = Animate::create(AnimationCache::getInstance()->getAnimation("glow")->clone());
	_glowEf->setDuration(0.5f);
	_glowEf->retain();

	_shootNode = Sprite::create();

	_shootNode->setPositionX(_shootPoint.x);
	_shootNode->setPositionY(_model->getContentSize().height / 2);
	// add listener
	auto listener = cocos2d::EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(Weapon::onMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	if (_model != nullptr)
	{
		_model->addChild(_shootNode);
		this->addChild(_model);
	}
	return true;
}

void Weapon::onMouseDown(cocos2d::EventMouse* event)
{
	attack(InputManager::getInstance()->mousePosition() - _parent->getParent()->getPosition());
}

void Weapon::attack(Vec2 direction)
{
	if (_cooldownTime > 0) return;
	_cooldownTime = _aspd;

	auto p = Projectile::createProjectile("projectile-2.png", "explosion");
	p->setSPD(650);
	p->setTimeLife(0.5f);
	p->launch(direction);
	p->setPosition(convertToWorldSpace(_shootPoint));
	p->setATK(_atk);

	_shootNode->stopAllActions();
	_shootNode->runAction(_glowEf->clone());
	AudioManager::getInstance()->playSFX(DefaultPath::AUDIO_PATH + "fire.mp3");
	Director::getInstance()->getRunningScene()->addChild(p);
}

void Weapon::update(float dt)
{
	if (_cooldownTime > 0) _cooldownTime -= dt;
}
