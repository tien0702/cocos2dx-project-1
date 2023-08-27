#include "EnemySpawner.h"
#include "Managers/GameManager.h"
#include "Maps/TiledMap.h"
#include "Scenes/GameScene/GameScene.h"

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
	_enemies.insert(std::pair<std::string, std::queue<EnemyController*>>("enemy-1", enemiesLst));
	for (int i = 0; i < 20; i++)
	{
		auto e = EnemyController::create("main");
		e->retain();
		_enemies.at("enemy-1").push(e);
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
	_gameScene->addChild(enemy, 3);
}

void EnemySpawner::onEnemyDie(EnemyController* enemy)
{
	GameManager::getInstance()->addScore(enemy->getLevel());
	_enemies.at("enemy-1").push(enemy);
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
		spawnEnemy("enemy-1");
	}
}
