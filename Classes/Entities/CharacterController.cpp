#include "CharacterController.h"
#include "Managers/InputManager.h"
#include "Managers/GameManager.h"
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
	GameManager::getInstance()->_onChangeEnemiesKilled
		.push_back(CC_CALLBACK_1(CharacterController::calculateStats, this));

	initComponents();
	this->addChild(_model, 1);
	this->addChild(_weaponAttachment);
	this->addChild(_healthBar, 50);
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
	this->calculateStats(0);
	_health->revive(0);
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

	_healthBar = HealthBar::create("Sprites/GUIs/health-border.png", "Sprites/GUIs/health-green-fill.png");
	float posY = _model->getContentSize().height / 2 + _healthBar->getChildren().at(0)->getContentSize().height / 2 + 10;
	_healthBar->setPositionY(posY);
	_healthBar->setHealthTarget(_health);
	// init body
	initBody();

	// weapon
	_weaponAttachment = Node::create();
	_weaponAttachment->setPositionY(0);
	auto wpModel = Sprite::create("weap-1.png");
	wpModel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	auto weapon = Weapon::create(wpModel,
		Vec2(wpModel->getContentSize().width, 0));

	this->equip(weapon);
	return true;
}

void CharacterController::takeDamage(int damage)
{
	EntityController::takeDamage(damage);
}

void CharacterController::equip(Weapon* weapon)
{
	if (this->_weapon != NULL) _weapon->removeFromParent();
	this->_weapon = weapon;
	_weapon->setATK(_atk);
	_weapon->setASPD(_aspd);
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
	Animation* idle, * move, * die;
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
	auto body = PhysicsBody::createCircle(_model->getContentSize().width * 0.5f, PhysicsMaterial(1, 1, 1));
	body->setCategoryBitmask(Bitmask::Player);
	body->setContactTestBitmask(Bitmask::Enemy);
	body->setCollisionBitmask(Bitmask::Wall);
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

void CharacterController::calculateStats(int numKilled)
{
	_hp = 100 + numKilled / 3;
	_atk = 30 + numKilled / 5;
	_spd = 150 + numKilled / 7;
	_aspd = 0.5f - (float)(numKilled / 15) * 0.05f;

	_weapon->setATK(_atk);
	_weapon->setASPD(_aspd);
	_health->recovery(_hp - _health->getMaxHP());
	_health->setMaxHP(_hp);
}

void CharacterController::move(Vec2 direction, float deltaTime)
{
	float spd = _spd;
	if (direction.x * (_model->isFlippedX() ? -1 : 1) < 0) spd = _spd * 0.7f;
	Vec2 offset = direction * spd;

	_physicsBody->setVelocity(offset);
}
