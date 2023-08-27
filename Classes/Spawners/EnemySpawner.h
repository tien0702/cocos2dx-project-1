#ifndef __ENEMY_SPAWNER_H__
#define __ENEMY_SPAWNER_H__

#include "cocos2d.h"
#include "Entities/EnemyController.h"

USING_NS_CC;

class GameScene;

class EnemySpawner : public Node
{
public:
	static EnemySpawner* getInstance();
protected:
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(EnemySpawner);
	void spawnEnemy(std::string name);
	void onEnemyDie(EnemyController* enemy);
	void onEnter();
protected:
	static EnemySpawner* _instance;
protected:
	CC_SYNTHESIZE(int, _maxEnemies, MaxEnemies);
	CC_SYNTHESIZE(int, _curEnemies, CurEnemies);
	CC_SYNTHESIZE(float, _delaySpawn, DelaySpawn);

	float _elapsedTime;

	std::map<std::string, std::queue<EnemyController*>> _enemies;
	Rect _spawnArea;
	GameScene* _gameScene;
};

#endif // !__ENEMY_SPAWNER_H__
