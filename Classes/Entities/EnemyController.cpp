#include "EnemyController.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Utilities.h"
#include "Utilities/Bitmask.h"
#include "Maps/TiledMap.h"
#include "Player/Player.h"


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
	_hp = 100;
	_atk = 15;
	_spd = 80;
	_level = 10;
	initComponents();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(EnemyController::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto eDieEf = AnimationCache::getInstance()->getAnimation("e-die")->clone();
	eDieEf->setDelayPerUnit(0.1f);
	_destroyEffect = Animate::create(eDieEf);
	_destroyEffect->retain();

	auto appear = Animate::create(AnimationCache::getInstance()->getAnimation("appear")->clone());
	auto idle = RepeatForever::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(_entityName + "-idle")->clone()));

	_health->registerEvent(Health::HealthEvent::OnDie, [&](int) {this->destroy(); });

	_state = EntityState::Move;
	_model->runAction(idle);
	this->addChild(_model);
	this->addChild(_healthBar, 100);
	return true;
}

void EnemyController::takeDamage(int damage)
{
	EntityController::takeDamage(damage);
	_health->takeDamage(damage);
	_state = EntityState::Hurt;
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
	Animation* hurt, * move, * attack, * die;
	move = Utilities::createAnimation(_entityName + "-move").first;
	hurt = Utilities::createAnimation(_entityName + "-hurt").first;
	die = Utilities::createAnimation(_entityName + "-die").first;

	aniCache->addAnimation(move, _entityName + "-move");
	aniCache->addAnimation(hurt, _entityName + "-hurt");
	aniCache->addAnimation(die, _entityName + "-die");

	return true;
}

bool EnemyController::initBody()
{
	auto body = PhysicsBody::createCircle(_model->getContentSize().width * 0.6f, PhysicsMaterial(1, 0, 1));
	body->setCategoryBitmask(Bitmask::Enemy);
	body->setContactTestBitmask(Bitmask::Player);
	body->setCollisionBitmask(Bitmask::None);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}

void EnemyController::update(float dt)
{
	switch (_state)
	{
	case EntityController::Move:
	{
		auto target = Player::getInstance()->getCharacter();
		Vec2 dir = target->getPosition() - _position;
		dir.normalize();
		this->move(dir, dt);

		if (dir.x != 0) _model->setFlippedX(dir.x < 0);
	}
		break;
	case EntityController::Hurt:
	{
		_cooldownHurtDelay -= dt;
		if (_cooldownHurtDelay <= 0)
		{
			_cooldownHurtDelay = _hurtDelay;
			_state = EntityState::Move;
		}
	}
		break;
	case EntityController::Die:
		break;
	default:
		break;
	}
}

void EnemyController::onEnter()
{
	EntityController::onEnter();
	_health->revive(0);
	this->scheduleUpdate();
	_health->registerEvent(Health::OnDie, [&](int) {
		for (auto callback : _onDie)
		{
			callback(this);
		}
		});
	auto idle = RepeatForever::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(_entityName + "-idle")->clone()));
	_model->runAction(idle);
}

void EnemyController::onExit()
{
	EntityController::onExit();
}

bool EnemyController::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return true;
	auto target = (nodeA == this ? (nodeB) : (nodeA));

	auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_atk);
		this->destroy();
	}

	return true;
}

void EnemyController::destroy()
{
	this->unscheduleUpdate();
	this->getPhysicsBody()->removeFromWorld();
	auto sequen = Sequence::createWithTwoActions(_destroyEffect->clone(),
		CallFunc::create([=]() {this->removeFromParent(); }));
	_model->stopAllActions();
	_model->runAction(sequen);
}
