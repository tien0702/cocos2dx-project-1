#include "EntityController.h"

bool EntityController::init()
{
	if (!Node::init())
	{
		log("init EntityController failed!");
		return false;
	}

	_health = new Health();
	return true;
}

void EntityController::takeDamage(int amount)
{
	_health->takeDamage(amount);
}

void EntityController::move(Vec2 direction, float deltaTime)
{
	this->setPosition(_position + direction * _spd * deltaTime);
}

void EntityController::onEnter()
{
	Node::onEnter();
	_health->setMaxHP(_hp);
}

void EntityController::onExit()
{
	Node::onExit();
}
