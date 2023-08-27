#include "GameManager.h"

GameManager* GameManager::_instance;

GameManager* GameManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager();
		_instance->init();
		_instance->retain();
	}
	return _instance;
}

void GameManager::addScore(int amount)
{
	_score += amount;
	for (auto callback : _onChangeScore)
	{
		callback(amount);
	}
}

void GameManager::destroy()
{
	this->autorelease();
}

bool GameManager::init()
{
	if (!Node::init())
	{
		log("init GameManager failed!");
		return false;
	}


	return true;
}

void GameManager::update(float dt)
{
	_gameTimer += dt;
}

void GameManager::onEnter()
{
	Node::onEnter();
}

void GameManager::onExit()
{
	Node::onExit();
}

void GameManager::spawnEnemy()
{
	_delaySpawn = 0.0f;
}
