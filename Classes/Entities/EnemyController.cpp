#include "EnemyController.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Utilities.h"
#include "Utilities/Bitmask.h"
#include "Maps/TiledMap.h"


EnemyController* EnemyController::create(std::string entityName)
{
	auto newTarget = new EnemyController();
	if (newTarget && newTarget->init(entityName))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool EnemyController::init(std::string entityName)
{
	if (!EntityController::init())
	{
		log("init EnemyController failed");
		return false;
	}
	this->_entityName = entityName;
	initComponents();
	_hp = 100;
	auto appear = Animate::create(AnimationCache::getInstance()->getAnimation("appear")->clone());
	auto idle = RepeatForever::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(_entityName + "-idle")->clone()));

	_model->runAction(idle);
	this->addChild(_model);
	this->addChild(_healthBar, 100);
	return true;
}

void EnemyController::takeDamage(int damage)
{
	EntityController::takeDamage(damage);
	_health->takeDamage(damage);
}


bool EnemyController::initComponents()
{
	initAnimation();
	this->_model = Sprite::createWithSpriteFrameName("./" + _entityName + "-idle (1)");
	_state = EntityController::Idle;
	_model->setPosition(Vec2::ZERO);
	_healthBar = HealthBar::create("Sprites/GUIs/health-border.png", "Sprites/GUIs/health-fill.png");
	float posY = _model->getContentSize().height / 2 + _healthBar->getChildren().at(0)->getContentSize().height / 2 + 10;
	_healthBar->setPositionY(posY);
	_healthBar->setHealthTarget(_health);
	initBody();
	return true;
}

bool EnemyController::initAnimation()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();

	// add SpriteFrames
	/*auto movePath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-move");
	auto hurtPath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-hurt");
	auto diePath = Utilities::initSpriteFramesPath(DefaultPath::ENTITIES_PATH, _entityName + "-die");
	spriteCache->addSpriteFramesWithFile(movePath.first, movePath.second);
	spriteCache->addSpriteFramesWithFile(hurtPath.first, hurtPath.second);
	spriteCache->addSpriteFramesWithFile(diePath.first, diePath.second);*/

	// add AnimationCache
	Animation* idle, * move, * attack, * die;
	move = Utilities::createAnimation(_entityName + "-move").first;
	idle = Utilities::createAnimation(_entityName + "-hurt").first;
	die = Utilities::createAnimation(_entityName + "-die").first;

	aniCache->addAnimation(move, _entityName + "-move");
	aniCache->addAnimation(idle, _entityName + "-hurt");
	aniCache->addAnimation(die, _entityName + "-die");

	return true;
}

bool EnemyController::initBody()
{
	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1));
	body->setCategoryBitmask(Bitmask::Enemy);
	body->setContactTestBitmask(Bitmask::Player);
	body->setCollisionBitmask(Bitmask::None);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}

void EnemyController::update(float dt)
{
}

void EnemyController::onEnter()
{
	EntityController::onEnter();
	_health->revive(0);
}

void EnemyController::onExit()
{
	EntityController::onExit();
}

