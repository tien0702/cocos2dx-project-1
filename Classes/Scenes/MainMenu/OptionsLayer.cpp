#include "OptionsLayer.h"
#include "GameConfig.h"
#include "Managers/AudioManager.h"

bool OptionsLayer::init()
{
	if (!SwallowTouchLayer::init())
	{
		log("init OptionsLayer failed!");
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// add background
	auto background = Sprite::create("bg-1.jpg");
	background->setPosition(visibleSize / 2);

	// init title
	auto title = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 70);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 70);

	// add button
	auto homeBtn = ui::Button::create();
	homeBtn->setTitleText("Back");
	homeBtn->setTitleFontName("fonts/Marker Felt.ttf");
	homeBtn->setTitleFontSize(40);
	homeBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
			{
				GameConfig::save();
				AudioManager::getInstance()->onClickBtn();
				this->removeFromParent();
			}
		});

	homeBtn->setPosition(Vec2(homeBtn->getContentSize().width / 2
		, visibleSize.height - homeBtn->getContentSize().height / 2));

	// init sliders
	initContent();
	_bgmSlider->setPosition((visibleSize / 2) + Size(-_bgmSlider->getContentSize().width / 2, 50));
	_sfxSlider->setPosition((visibleSize / 2) + Size(-_bgmSlider->getContentSize().width / 2, -50));

	this->addChild(_bgmSlider);
	this->addChild(_sfxSlider);
	this->addChild(background, -1);
	this->addChild(homeBtn, 1);
	this->addChild(title, 1);
	return true;
}

bool OptionsLayer::initContent()
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
