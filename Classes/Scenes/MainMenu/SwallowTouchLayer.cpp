#include "SwallowTouchLayer.h"

bool SwallowTouchLayer::init()
{
	if (!Layer::init())
	{
		log("init SwallowTouchLayer failed!");
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SwallowTouchLayer::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SwallowTouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
