#include "EnemySpawner.h"
#include "Managers/GameManager.h"
#include "Maps/TiledMap.h"
#include "Scenes/GameScene/GameScene.h"
#include "GUIs/FloatingNumber.h"

EnemySpawner* EnemySpawner::_instance;

EnemySpawner* EnemySpawner::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = EnemySpawner::create();
		_instance->retain();
	}
	return _instance;
}

bool EnemySpawner::init()
{
	if (!Node::init())
	{
		return false;
	}

	_maxEnemies = 10;
	_curEnemies = 0;
	_delaySpawn = 1.0f;

	auto areaVal = TiledMap::_mainMap->getObjectInPoint("SpawnArea");
	_spawnArea.origin.x = areaVal["x"].asFloat();
	_spawnArea.origin.y = areaVal["y"].asFloat();
	_spawnArea.size.width = areaVal["width"].asFloat();
	_spawnArea.size.height = areaVal["height"].asFloat();

	//
	std::queue<EnemyController*> enemiesLst;
	_enemies.insert(std::pair<std::string, std::queue<EnemyController*>>("wing-dron", enemiesLst));
	for (int i = 0; i < 20; i++)
	{
		auto e = EnemyController::create("wing-dron");
		e->retain();
		_enemies.at(e->getEntityName()).push(e);
	}
	return true;
}

void EnemySpawner::spawnEnemy(std::string name)
{
	auto enemy = _enemies.at(name).front();
	_enemies.at(name).pop();
	_curEnemies++;
	enemy->_onDie.push_back(CC_CALLBACK_1(EnemySpawner::onEnemyDie, this));

	float x = RandomHelper::random_real(_spawnArea.origin.x, _spawnArea.origin.x + _spawnArea.size.width);
	float y = RandomHelper::random_real(_spawnArea.origin.y, _spawnArea.origin.y + _spawnArea.size.height);
	enemy->setPosition(x, y);

	calculateStats(enemy);

	_gameScene->addChild(enemy, 3);
}

void EnemySpawner::calculateStats(EnemyController* enemy)
{
	double duration = GameManager::getInstance()->getGameTimer();
	enemy->setLevel(duration + 1);

	enemy->setHP(100 + duration / 15);

	float atk = 10 + duration  / 10.0f;
	enemy->setATK(atk);

	float spd = 70 + duration / 30.0f;
	enemy->setSPD(spd);
}

void EnemySpawner::onEnemyDie(EnemyController* enemy)
{
	int score = enemy->getLevel();
	GameManager::getInstance()->addScore(score);
	GameManager::getInstance()->addEnemyKilled(1);
	FloatingNumber::getIns()->floatText(enemy->getPosition(), "+" + std::to_string(score), Color4B::YELLOW);

	_curEnemies--;
}

void EnemySpawner::onEnter()
{
	Node::onEnter();
	_gameScene = dynamic_cast<GameScene*>(_parent);
	this->scheduleUpdate();
}

void EnemySpawner::update(float dt)
{
	if (_curEnemies >= _maxEnemies) return;
	_elapsedTime += dt;

	if (_elapsedTime >= _delaySpawn)
	{
		_elapsedTime = 0;
		spawnEnemy("main");
	}
}

void EnemySpawner::add(EnemyController* enemy)
{
	_enemies.at(enemy->getEntityName()).push(enemy);
}
