#include "FloatingNumber.h"

FloatingNumber* FloatingNumber::_instance;

FloatingNumber::FloatingNumber()
{
	_font = GameConfig::_font;
	_font.fontSize *= 0.6f;
	float timeScale = 0.2f;
	float scaleSize = 1.3f;
	auto zoomIN = ScaleBy::create(timeScale, scaleSize);
	auto zoomOut = zoomIN->reverse();
	_zoom = Sequence::createWithTwoActions(zoomIN, zoomOut);
	_zoom->retain();

}

FloatingNumber* FloatingNumber::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new FloatingNumber();
	}

	return _instance;
}

void FloatingNumber::floatText(Vec2 position, std::string content, Color4B color)
{
	Label* label = Label::createWithTTF(_font, content);
	label->setTextColor(color);

	float timeShow = RandomHelper::random_real(0.5f, 0.75f);
	int x = RandomHelper::random_int(-20, 20);
	int y = RandomHelper::random_int(10, 20);


	auto jump = JumpBy::create(timeShow, Vec2(x, 0), y, 1);
	auto remove = CallFunc::create([=]() {label->removeFromParent(); });
	label->runAction(Sequence::createWithTwoActions(jump, remove));
	label->setPosition(position);

	Director::getInstance()->getRunningScene()->addChild(label, 50);
}
