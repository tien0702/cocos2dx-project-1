#include "HealthBar.h"
#include "GUIs/FloatingNumber.h"

HealthBar* HealthBar::create(std::string borderPath, std::string fillPath)
{
	auto newTarget = new HealthBar();
	if (newTarget && newTarget->init(borderPath, fillPath))
	{
		newTarget->autorelease();
		return newTarget;
	}
	CC_SAFE_DELETE(newTarget);
	return nullptr;
}

bool HealthBar::init(std::string borderPath, std::string fillPath)
{
	if (!Sprite::create())
	{
		log("init HealthBar failed!");
		return false;
	}

	_border = Sprite::create(borderPath);
	_fill = Sprite::create(fillPath);
	_fill->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_fill->setPositionX(-_fill->getContentSize().width / 2);

	this->addChild(_border, 0);
	this->addChild(_fill, 1);
	return true;
}

void HealthBar::onEnter()
{
	Sprite::onEnter();
}

void HealthBar::onExit()
{
	Sprite::onExit();
}

void HealthBar::onHPChange(int val)
{
	int curVal = _healthTarget->getCurrentHP();
	int maxVal = _healthTarget->getMaxHP();
	_fill->setScaleX(((float)curVal / (float)maxVal));

	if (val < 0)
		FloatingNumber::getIns()->floatText(_parent->getPosition(), std::to_string(val), Color4B::RED);
	else
		FloatingNumber::getIns()->floatText(_parent->getPosition(), "+" + std::to_string(val), Color4B::GREEN);
}

void HealthBar::setHealthTarget(Health* healthTarget)
{
	if (_healthTarget != nullptr)
	{
		_healthTarget->unregisterEvent(Health::HealthEvent::OnTakeDamage, CC_CALLBACK_1(HealthBar::onHPChange, this));
		_healthTarget->unregisterEvent(Health::HealthEvent::OnRecovery, CC_CALLBACK_1(HealthBar::onHPChange, this));
		_healthTarget->unregisterEvent(Health::HealthEvent::OnRevive, CC_CALLBACK_1(HealthBar::onHPChange, this));
	}
	this->_healthTarget = healthTarget;
	_healthTarget->registerEvent(Health::HealthEvent::OnTakeDamage, CC_CALLBACK_1(HealthBar::onHPChange, this));
	_healthTarget->registerEvent(Health::HealthEvent::OnRecovery, CC_CALLBACK_1(HealthBar::onHPChange, this));
	_healthTarget->registerEvent(Health::HealthEvent::OnRevive, CC_CALLBACK_1(HealthBar::onHPChange, this));
}
