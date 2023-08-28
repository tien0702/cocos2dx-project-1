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

    /*_character->setHP(100);
    _character->setATK(30);
    _character->setASPD(0.3f);
    _character->setSPD(150);*/
    _character->retain();
}


CharacterController* Player::getCharacter()
{
    return _character;
}
