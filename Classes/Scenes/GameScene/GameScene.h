#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Entities/EntityController.h"
#include "Entities/EnemyController.h"
#include "Entities/CharacterController.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
protected:
	void onEnter();
	void onExit();
	void update(float dt);

	CharacterController* _char;
protected:
};

#endif // !__GAME_SCENE_H__
