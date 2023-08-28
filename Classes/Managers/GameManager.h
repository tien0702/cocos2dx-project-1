#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Entities/EnemyController.h"

USING_NS_CC;

using namespace std;

class GameManager : public Node
{
public:
	static GameManager* getInstance();
	vector<function<void(int)>> _onChangeScore;
	vector<function<void(int)>> _onChangeEnemiesKilled;

	void addScore(int amount);
	void addEnemyKilled(int amount);
	void destroy();
protected:
	virtual bool init();
	virtual void update(float dt);
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameManager);
protected:
	static GameManager* _instance;
	int _score = 0;
	int _enemiesKilled = 0;

	CC_SYNTHESIZE(double, _gameTimer, GameTimer);

};

#endif // !__GAME_MANAGER_H__
