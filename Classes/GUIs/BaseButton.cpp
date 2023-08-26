#include "BaseButton.h"
#include "Managers/AudioManager.h"

bool BaseButton::init()
{
    if (!ui::Button::init())
    {
        log("init BaseButton failed!");
        return false;
    }

    this->addTouchEventListener(CC_CALLBACK_2(BaseButton::onButtonPressed, this));
    return true;
}

void BaseButton::onButtonPressed(Ref* sender, ui::Widget::TouchEventType eventType)
{
    AudioManager::getInstance()->onClickBtn();
}
