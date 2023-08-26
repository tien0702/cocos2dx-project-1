#include "Projectile.h"
#include "Managers/AudioManager.h"
#include "Utilities/Utilities.h"
#include "Utilities/DefaultPath.h"
#include "DamageSystem/IDamageable.h"
#include "Utilities/Bitmask.h"

Projectile* Projectile::createProjectile(std::string imgPath, std::string destroyEfName)
{
	auto newTarget = new Projectile();
	if (newTarget && newTarget->init(imgPath, destroyEfName))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool Projectile::init(std::string imgPath, std::string destroyEfName)
{
	if (!Sprite::initWithFile(imgPath))
	{
		log("init Projectile failed!");
		return false;
	}


	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(DefaultPath::EFFECT_PATH + destroyEfName + ".plist",
		DefaultPath::EFFECT_PATH + destroyEfName + ".png");
	_destroyEffect = Animate::create(AnimationCache::getInstance()->getAnimation("explosion")->clone());
	_destroyEffect->retain();

	initBody();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Projectile::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void Projectile::launch(Vec2 direction)
{
	_cooldownTime = _timeLife;
	_shootDirection = direction;
	_shootDirection.normalize();

	float rotation = Vec2::angle(Vec2::ANCHOR_BOTTOM_RIGHT, direction);
	if (direction.y > 0)
		rotation = -rotation;
	this->setRotation(rotation);

	this->scheduleUpdate();
}

void Projectile::destroy()
{
	this->unscheduleUpdate();
	this->getPhysicsBody()->removeFromWorld();
	AudioManager::getInstance()->playSFX(DefaultPath::AUDIO_PATH + "explosion.mp3");
	auto sequen = Sequence::createWithTwoActions(_destroyEffect->clone(), 
		CallFunc::create([=]() {this->removeFromParent(); }));
	this->runAction(sequen);
}

void Projectile::update(float dt)
{
	_cooldownTime -= dt;
	if (_cooldownTime <= 0)
	{
		destroy();
		return;
	}

	this->setPosition(_position + _shootDirection * _spd * dt);
}


bool Projectile::onContactBegin(const PhysicsContact& contact)
{
	if (_isContact) return true;
	_isContact = true;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return true;
	auto target = (nodeA == this ? (nodeB) : (nodeA));

	auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr) damageable->takeDamage(this->_atk);
	destroy();

	return true;
}

bool Projectile::initBody()
{
	auto body = PhysicsBody::createCircle(_contentSize.width / 2, PhysicsMaterial(1, 0, 1));
	body->setCategoryBitmask(Bitmask::Projectile);
	body->setContactTestBitmask(Bitmask::Enemy);
	body->setCollisionBitmask(Bitmask::None);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}
