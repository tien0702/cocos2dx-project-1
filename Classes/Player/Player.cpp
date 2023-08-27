#include "Player.h"

Player* Player::_instance;

Player* Player::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Player();
    }

    return _instance;
}

Player::Player()
{
    _character = CharacterController::create("main");
    _character->setSPD(170);
    _character->retain();
}


CharacterController* Player::getCharacter()
{
    return _character;
}
