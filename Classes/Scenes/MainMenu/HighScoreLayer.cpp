#include "HighScoreLayer.h"
#include "Utilities/Utilities.h"
#include "Managers/AudioManager.h"

HighScoreLayer* HighScoreLayer::createHighScoreLayer(Size tableSize, float padding, int charNum)
{
	auto layer = new HighScoreLayer();
	if (layer && layer->init(tableSize, padding, charNum))
	{
		layer->autorelease();
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool HighScoreLayer::init(Size tableSize, float padding, int charNum)
{
	if (!SwallowTouchLayer::init())
	{
		log("init HighScore failed!");
		return false;
	}
	// init first values
	this->_tableSize = tableSize;
	this->_padding = padding;
	this->_charactersNum = charNum;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// add background
	auto background = Sprite::create("bg-1.jpg");
	background->setPosition(visibleSize / 2);

	// init title
	auto title = Label::createWithTTF("High Score", "fonts/Marker Felt.ttf", 70);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 70);

	// add button
	auto button = ui::Button::create();
	button->setTitleText("Back");
	button->setTitleFontName("fonts/Marker Felt.ttf");
	button->setTitleFontSize(40);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if(type == ui::Widget::TouchEventType::BEGAN)
				AudioManager::getInstance()->onClickBtn();
			if (type == ui::Widget::TouchEventType::ENDED) this->removeFromParent();
		});

	button->setPosition(Vec2(button->getContentSize().width / 2
		, visibleSize.height - button->getContentSize().height / 2));

	// init table scroll view
	initTableScrollView();
	_tableScrollView->setPosition((visibleSize / 2.0f) - _tableScrollView->getContentSize() / 2);

	this->addChild(background, -1);
	this->addChild(button, 1);
	this->addChild(title, 1);
	this->addChild(_tableScrollView, 1);
	return true;
}

bool HighScoreLayer::initTableScrollView()
{
	_tableScrollView = ui::ScrollView::create();
	_tableScrollView->setContentSize(_tableSize);
	_tableScrollView->setDirection(ui::ScrollView::Direction::VERTICAL);

	// init children
	auto children = new cocos2d::Vector<cocos2d::Node*>();
	for (int i = 0; i < 1; ++i)
	{
		auto str = Utilities::justifyStrings("Label", std::to_string(i), _charactersNum);
		auto label = cocos2d::Label::createWithTTF(str, "fonts/Marker Felt.ttf", 24);
		label->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
		children->pushBack(label);
	}

	// calculate innerContentSize and set position for children
	Size innerSize;
	innerSize.width = _tableSize.width;
	innerSize.height = (children->front()->getContentSize().height + _padding) * children->size();

	int size = children->size();
	float childSizeH = children->front()->getContentSize().height;
	for (int i = 0; i < size; ++i)
	{
		children->at(i)->setPosition(_tableScrollView->getContentSize().width / 2,
			innerSize.height - (i * childSizeH + i * _padding));
		_tableScrollView->addChild(children->at(i));
	}

	_tableScrollView->setInnerContainerSize(innerSize);
	_tableScrollView->setBounceEnabled(true);
	_tableScrollView->setScrollBarOpacity(0);
	_tableScrollView->jumpToTop();
	return true;
}
