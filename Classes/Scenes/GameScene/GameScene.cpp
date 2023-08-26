#include "GameScene.h"
#include "Managers/InputManager.h"
#include "Managers/AudioManager.h"
#include "Maps/TiledMap.h"
#include "GUIs/FollowCursor.h"
#include "GUIs/MouseClickEffect.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Utilities.h"
#include "Camera/CameraFollowTarget.h"
#include "GUIs/HUDLayer/HUDLayer.h"

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		log("init GameScene failed!");
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2::ZERO);
	// init animation
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile(DefaultPath::EFFECT_PATH + "explosion" + ".plist",
		DefaultPath::EFFECT_PATH + "explosion" + ".png");
	auto explosion = Utilities::createAnimation("explosion");
	AnimationCache::getInstance()->addAnimation(explosion.first, "explosion");

	// init map
	auto map = new TiledMap();
	map->initWithTMXFile("Tilemaps/map2.tmx");

	_char = CharacterController::create("main");
	_char->setPosition(200, 200);
	_char->setSPD(170);

	auto enemy = EnemyController::create("main");
	enemy->setPosition(500, 500);

	this->addChild(enemy, 3);

	// camera
	auto cameraFl = CameraFollowTarget::create(_defaultCamera, _char, 0.05f);

	this->addChild(map);
	this->addChild(cameraFl);
	this->addChild(_char);
	this->addChild(HUDLayer::getInstance(), 100);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	InputManager::getInstance()->removeFromParent();
	FollowCursor::getInstance()->removeFromParent();
	AudioManager::getInstance()->playBGM(DefaultPath::AUDIO_PATH + "battle-bgm.mp3");

	InputManager::getInstance()->setTargetCam(_defaultCamera);
	FollowCursor::getInstance()->initWithFile("cursor1.png");

	this->addChild(FollowCursor::getInstance());
	this->addChild(InputManager::getInstance());

	this->scheduleUpdate();
}

void GameScene::onExit()
{
	Scene::onExit();
}

void GameScene::update(float dt)
{
}
