#include "GameScene.h"
#include "Managers/InputManager.h"
#include "Managers/AudioManager.h"
#include "Managers/GameManager.h"
#include "Maps/TiledMap.h"
#include "GUIs/FollowCursor.h"
#include "GUIs/MouseClickEffect.h"
#include "Utilities/DefaultPath.h"
#include "Utilities/Bitmask.h"
#include "Utilities/Utilities.h"
#include "Camera/CameraFollowTarget.h"
#include "GUIs/HUDLayer/HUDLayer.h"
#include "Player/Player.h"
#include "Spawners/EnemySpawner.h"

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

	// load ani Cache
	std::vector<std::string> aniLst;
	aniLst.push_back("explosion");
	aniLst.push_back("appear");
	aniLst.push_back("glow");
	aniLst.push_back("e-die");

	Utilities::loadAnimationsCache(aniLst);

	// init map
	auto map = new TiledMap();
	map->initWithTMXFile("Tilemaps/map2.tmx");

	_char = Player::getInstance()->getCharacter();

	auto posVal = TiledMap::_mainMap->getObjectInPoint("SpawnPosition");
	_char->setPosition(posVal["x"].asFloat(), posVal["y"].asFloat());

	auto spawnAreaVal = TiledMap::_mainMap->getObjectInPoint("SpawnArea");
	Size spawnArea = Size(spawnAreaVal["width"].asFloat(), spawnAreaVal["height"].asFloat());

	auto body = PhysicsBody::createEdgeBox(spawnArea, PhysicsMaterial(1, 1, 1), 10);
	body->setCategoryBitmask(Bitmask::Wall);
	body->setContactTestBitmask(Bitmask::All);
	body->setCollisionBitmask(Bitmask::All);
	body->setRotationEnable(false);
	auto bodyHolder = Node::create();
	bodyHolder->setPhysicsBody(body);
	bodyHolder->setPosition(TiledMap::_mainMap->getContentSize() / 2);

	this->addChild(EnemySpawner::getInstance());
	this->addChild(bodyHolder);
	this->addChild(map);
	this->addChild(CameraFollowTarget::create(_defaultCamera, _char, 0.05f));
	this->addChild(_char);
	this->addChild(HUDLayer::getInstance(), 100);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	InputManager::getInstance()->removeFromParent();
	FollowCursor::getInstance()->removeFromParent();
	GameManager::getInstance()->removeFromParent();
	AudioManager::getInstance()->playBGM(DefaultPath::AUDIO_PATH + "battle-bgm.mp3");

	InputManager::getInstance()->setTargetCam(_defaultCamera);
	FollowCursor::getInstance()->initWithFile("cursor1.png");

	this->addChild(FollowCursor::getInstance());
	this->addChild(InputManager::getInstance());
	this->addChild(GameManager::getInstance());

	this->scheduleUpdate();
}

void GameScene::onExit()
{
	Scene::onExit();
}

void GameScene::update(float dt)
{
}
