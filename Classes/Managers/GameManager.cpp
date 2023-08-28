#include "GameManager.h"

GameManager* GameManager::_instance;

GameManager* GameManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = GameManager::create();
		_instance->retain();
	}
	return _instance;
}

void GameManager::addScore(int amount)
{
	_score += amount;
	for (auto callback : _onChangeScore)
	{
		callback(_score);
	}
}

void GameManager::addEnemyKilled(int amount)
{
	_enemiesKilled += amount;
	for (auto callback : _onChangeEnemiesKilled)
	{
		callback(_enemiesKilled);
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

	_gameTimer = 0.0;
	this->scheduleUpdate();
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
