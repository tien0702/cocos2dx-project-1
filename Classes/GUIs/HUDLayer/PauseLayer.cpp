#include "PauseLayer.h"
#include "Managers/AudioManager.h"
#include "GameConfig.h"

bool PauseLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(51, 0, 0, 150)))
	{
		log("init PauseLayer failed!");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// init title
	auto title = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 70);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 70);

	// add button
	auto backBtn = ui::Button::create();
	backBtn->setTitleText("Back");
	backBtn->setTitleFontName("fonts/Marker Felt.ttf");
	backBtn->setTitleFontSize(40);
	backBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
			{
				this->removeFromParent();

				GameConfig::save();
				AudioManager::getInstance()->onClickBtn();
				auto runningScene = Director::getInstance()->getRunningScene();
				auto objs = runningScene->getChildren();
				auto eventDis = Director::getInstance()->getEventDispatcher();
				for each (auto obj in objs)
				{
					obj->resume();
					eventDis->resumeEventListenersForTarget(obj, true);
				}
			}
		});

	backBtn->setPosition(Vec2(backBtn->getContentSize().width / 2
		, visibleSize.height - backBtn->getContentSize().height / 2));

	// init sliders
	initContent();
	_bgmSlider->setPosition((visibleSize / 2) + Size(-_bgmSlider->getContentSize().width / 2, 50));
	_sfxSlider->setPosition((visibleSize / 2) + Size(-_bgmSlider->getContentSize().width / 2, -50));


	//

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event) {return true; };
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(_bgmSlider);
	this->addChild(_sfxSlider);
	this->addChild(backBtn, 1);
	this->addChild(title, 1);
}

bool PauseLayer::initContent()
{

	Label* BG, * SFX;
	BG = Label::createWithTTF("BG Music", "fonts/Marker Felt.ttf", 35);
	SFX = Label::createWithTTF("SFX", "fonts/Marker Felt.ttf", 35);


	_sfxSlider = ui::Slider::create();
	_sfxSlider = cocos2d::ui::Slider::create();
	_sfxSlider->loadBarTexture("track1.png");
	_sfxSlider->loadSlidBallTextureNormal("thumb-slide1.png");
	_sfxSlider->loadProgressBarTexture("progress1.png");
	_sfxSlider->setPercent(GameConfig::_sfxVolume * 100.0f);
	_sfxSlider->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sfxSlider->addChild(SFX);
	_sfxSlider->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType)
		{
			if (eventType == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN)
			{
				AudioManager::getInstance()->onClickBtn();
			}
			else if (eventType == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
				int percent = slider->getPercent();
				AudioManager::getInstance()->setVolumeSFX(percent * 0.01f);
			}
		});

	_bgmSlider = ui::Slider::create();
	_bgmSlider = cocos2d::ui::Slider::create();
	_bgmSlider->loadBarTexture("track1.png");
	_bgmSlider->loadSlidBallTextureNormal("thumb-slide1.png");
	_bgmSlider->loadProgressBarTexture("progress1.png");
	_bgmSlider->setPercent(GameConfig::_bgmVolume * 100.0f);
	_bgmSlider->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_bgmSlider->addChild(BG);
	_bgmSlider->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType)
		{
			if (eventType == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN)
			{
				AudioManager::getInstance()->onClickBtn();
			}
			else if (eventType == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
				int percent = slider->getPercent();
				AudioManager::getInstance()->setVolumeBGM(percent * 0.01f);
			}
		});

	auto textPostion = Vec2(-80, _bgmSlider->getContentSize().height / 2);
	BG->setPosition(textPostion);
	SFX->setPosition(textPostion);
	return true;
}
