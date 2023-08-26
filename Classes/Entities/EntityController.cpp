#include "EntityController.h"

bool EntityController::init()
{
	if (!Node::init())
	{
		log("init EntityController failed!");
		return false;
	}


	return true;
}

void EntityController::move(Vec2 direction, float deltaTime)
{
	this->setPosition(_position += direction * _spd * deltaTime);
}
