#include "HUDLayer.h"
#include "GUIs/FollowCursor.h"
#include "Managers/InputManager.h"
#include "Managers/GameManager.h"
#include "Utilities/Utilities.h"
#include "GameConfig.h"

HUDLayer* HUDLayer::_instance;

HUDLayer* HUDLayer::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new HUDLayer();
		_instance->init();
	}
	return _instance;
}

bool HUDLayer::init()
{
	if (!Layer::init())
	{
		log("init HUDLayer failed!");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//layer
	_pauseLayer = PauseLayer::create();
	_pauseLayer->retain();
	// bnt
	auto pauseBtn = ui::Button::create();
	pauseBtn->setTitleText("Pause");
	pauseBtn->setTitleFontName("fonts/Marker Felt.ttf");
	pauseBtn->setTitleFontSize(40);
	pauseBtn->addTouchEventListener(CC_CALLBACK_2(HUDLayer::pauseCallback, this));
	pauseBtn->setSwallowTouches(true);
	pauseBtn->setPosition(_contentSize - pauseBtn->getContentSize() / 2);

	// Labels
	auto font = GameConfig::_font;
	font.fontSize = 20;
	_scoreText = Label::createWithTTF(font, "Score: 0");
	_timerText = Label::createWithTTF(font, "0");

	_scoreText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_timerText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	_timerText->setAlignment(TextHAlignment::LEFT);
	_scoreText->setAlignment(TextHAlignment::LEFT);

	_scoreText->setPosition(30, visibleSize.height - 50);
	_timerText->setPosition(30 / 2, visibleSize.height - 100);

	GameManager::getInstance()->_onChangeScore.push_back([&](int score) {
		_scoreText->setString("Score: " + std::to_string(score));
		});

	this->addChild(_scoreText);
	this->addChild(_timerText);
	this->addChild(pauseBtn);
	return true;
}

void HUDLayer::pauseCallback(Ref* sender, ui::Widget::TouchEventType eventType)
{
	if (_showingPauseLayer) return;
	_showingPauseLayer = true;
	auto runningScene = Director::getInstance()->getRunningScene();

	auto objs = runningScene->getChildren();
	auto eventDis = Director::getInstance()->getEventDispatcher();
	for each (auto obj in objs)
	{
		if (obj == FollowCursor::getInstance()) continue;
		if (obj == InputManager::getInstance()) continue;
		obj->pause();
		eventDis->pauseEventListenersForTarget(obj, true);
	}
	_pauseLayer->setPosition(runningScene->getDefaultCamera()->getPosition()
		- Director::getInstance()->getVisibleSize() / 2);
	runningScene->addChild(_pauseLayer, 100);
}

void HUDLayer::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
}

void HUDLayer::update(float dt)
{
	_mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
	this->setPosition(_mainCam->getPosition() - _contentSize / 2);
	_timerText->setString("Time: " + Utilities::doubleToTime(GameManager::getInstance()->getGameTimer()));
}

void HUDLayer::onExit()
{
	Layer::onExit();
}

void HUDLayer::resume()
{
	Layer::resume();
	_showingPauseLayer = false;
}
