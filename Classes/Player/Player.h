#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entities/CharacterController.h"	

class Player
{
public:
	static Player* getInstance();
	CharacterController* getCharacter();
private:
	Player();
	CharacterController* _character;
private:
	static Player* _instance;
};

#endif // !__PLAYER_H__
