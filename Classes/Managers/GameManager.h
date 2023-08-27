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

	void addScore(int amount);
	void destroy();
protected:
	virtual bool init();
	virtual void update(float dt);
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameManager);
protected:
	virtual void spawnEnemy();
protected:
	static GameManager* _instance;
	vector<EnemyController*> _enemies;
	int _score;

	int numOfSpawn = 5;
	float _delaySpawn = 0.2f;
	CC_SYNTHESIZE(double, _gameTimer, GameTimer);

};

#endif // !__GAME_MANAGER_H__
