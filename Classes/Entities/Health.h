#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "cocos2d.h"

using namespace std;

class Health
{
public:
	enum HealthEvent { OnTakeDamage, OnRecovery, OnRevive, OnDie };

	void registerEvent(HealthEvent eventId, function<void(int)> callback);
	void unregisterEvent(HealthEvent eventId, function<void(int)> callback);
	void clearAllHealthEvents();
	void notifyEvent(HealthEvent eventID, int param);

public:
	void takeDamage(int amount);
	void recovery(int amount);
	void revive(int amount);
protected:
	CC_SYNTHESIZE(int, _maxHP, MaxHP);
	CC_SYNTHESIZE(int, _currentHP, CurrentHP);
	map<HealthEvent, vector<function<void(int)>>> _observerEvents;
};

#endif // !__HEALTH_H__
