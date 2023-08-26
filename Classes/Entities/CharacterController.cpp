#include "CharacterController.h"
#include "Managers/InputManager.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Utilities.h"
#include "Utilities/Bitmask.h"
#include "Maps/TiledMap.h"

CharacterController* CharacterController::create(std::string entityName)
{
	auto newTarget = new CharacterController();
	if (newTarget && newTarget->init(entityName))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool CharacterController::init(std::string entityName)
{
	if (!EntityController::init())
	{
		log("init CharacterController failed");
		return false;
	}
	this->_entityName = entityName;
	initComponents();
	this->addChild(_model, 1);
	this->addChild(_weaponAttachment);
	return true;
}


void CharacterController::update(float dt)
{
	this->weaponLookAtMouse();
	this->lookAtMouse();
	auto input = InputManager::getInstance();
	switch (_state)
	{
	case EntityController::Idle:
		if (input->inputDirection() != Vec2::ZERO)
		{
			auto moveAni = AnimationCache::getInstance()->getAnimation(_entityName + "-move");
			auto ani = RepeatForever::create(Animate::create(moveAni));
			ani->setTag(1);
			_model->stopActionByTag(1);
			_model->runAction(ani);
			_state = EntityController::Move;
		}
		break;
	case EntityController::Move:
		// update state
		this->move(input->inputDirection(), dt);
		// check state
		if (input->inputDirection() == Vec2::ZERO)
		{
			auto idleAni = AnimationCache::getInstance()->getAnimation(_entityName + "-idle");
			auto ani = RepeatForever::create(Animate::create(idleAni));
			ani->setTag(1);
			_model->stopActionByTag(1);
			_model->runAction(ani);
			_state = EntityController::Idle;
		}
		break;
	case EntityController::Attack:
		break;
	case EntityController::Die:
		break;
	default:
		break;
	}
}

void CharacterController::onEnter()
{
	EntityController::onEnter();
	_model->runAction(RepeatForever::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(_entityName + "-idle"))));
	this->scheduleUpdate();
}

void CharacterController::onExit()
{
	EntityController::onExit();
}

bool CharacterController::initComponents()
{
	initAnimation();

	this->_model = Sprite::createWithSpriteFrameName("./" + _entityName + "-idle (1)");
	_state = EntityController::Idle;
	_model->setPosition(Vec2::ZERO);

	// init body
	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.5f);
	this->setPhysicsBody(body);

	// weapon
	_weaponAttachment = Node::create();
	_weaponAttachment->setPositionY(0);
	auto wpModel = Sprite::create("trident staff.png");
	wpModel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	auto weapon = Weapon::createWeapon(wpModel,
		Vec2(wpModel->getContentSize().width, 0));
	weapon->setASPD(0.3f);

	this->equip(weapon);
	return true;
}

void CharacterController::takeDamage(int damage)
{
	_currentHP = MAX(0, _currentHP - damage);
	if (_currentHP == 0) log("die");
}

void CharacterController::equip(Weapon* weapon)
{
	if (this->_weapon != NULL) _weapon->removeFromParent();
	this->_weapon = weapon;
	_weapon->setPosition(15, 0);
	_weaponAttachment->addChild(_weapon);
}

bool CharacterController::initAnimation()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();

	// add SpriteFrames
	auto idlePath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-idle");
	auto movePath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-move");
	//auto attackPath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-attack");
	auto diePath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-die");
	spriteCache->addSpriteFramesWithFile(idlePath.first, idlePath.second);
	spriteCache->addSpriteFramesWithFile(movePath.first, movePath.second);
	//spriteCache->addSpriteFramesWithFile(attackPath.first, attackPath.second);
	spriteCache->addSpriteFramesWithFile(diePath.first, diePath.second);

	// add AnimationCache
	Animation* idle, * move, * attack, * die;
	idle = Utilities::createAnimation(_entityName + "-idle").first;
	move = Utilities::createAnimation(_entityName + "-move").first;
	//attack = Utilities::createAnimation(_entityName + "-attack").first;
	die = Utilities::createAnimation(_entityName + "-die").first;

	aniCache->addAnimation(idle, _entityName + "-idle");
	aniCache->addAnimation(move, _entityName + "-move");
	aniCache->addAnimation(die, _entityName + "-die");

	return true;
}

bool CharacterController::initBody()
{
	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1));
	body->setCategoryBitmask(Bitmask::Player);
	body->setContactTestBitmask(Bitmask::None);
	body->setCollisionBitmask(Bitmask::None);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}

void CharacterController::weaponLookAtMouse()
{
	Vec2 direction = InputManager::getInstance()->mousePosition() - _position;
	float rotation = Vec2::angle(Vec2::ANCHOR_BOTTOM_RIGHT, direction);
	if (direction.y > 0)
		rotation = -rotation;
	_weaponAttachment->setRotation(CC_RADIANS_TO_DEGREES(rotation));
}

void CharacterController::lookAtMouse()
{
	Vec2 direction = InputManager::getInstance()->mousePosition() - _position;
	if (direction.x != 0) _model->setFlippedX(direction.x < 0);
}

void CharacterController::move(Vec2 direction, float deltaTime)
{
	float spd = _spd;
	if (direction.x * (_model->isFlippedX() ? -1 : 1) < 0) spd = _spd * 0.7f;
	Vec2 offset = direction * spd * deltaTime;
	Vec2 nextPosition = _position + offset;

	TiledMap::MetaType metaType = TiledMap::_mainMap->getMetaAt(nextPosition);
	if (metaType == TiledMap::MetaType::InsideRed) return;

	this->setPosition(nextPosition);
}