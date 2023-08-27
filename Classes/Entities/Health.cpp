#include "Health.h"

void Health::registerEvent(HealthEvent eventId, function<void(int)> callback)
{
	if (_observerEvents.find(eventId) == _observerEvents.end())
	{
		vector<function<void(int)>> callbacks;
		auto val = pair<HealthEvent, vector<function<void(int)>>>(eventId, callbacks);
		_observerEvents.insert(val);
	}

	_observerEvents[eventId].push_back(callback);
}

void Health::unregisterEvent(HealthEvent eventId, function<void(int)> callback)
{
	if (_observerEvents.find(eventId) == _observerEvents.end())
	{
		return;
	}

	auto callbacks = _observerEvents[eventId];
	callbacks.erase(remove_if(callbacks.begin(), callbacks.end(),
		[&](const function<void(int)>& func) {
			return func.target<void(int)>() == callback.target<void(int)>();
		}),
		callbacks.end());
}

void Health::clearAllHealthEvents()
{
	for (auto ev : _observerEvents)
	{
		ev.second.clear();
	}
}

void Health::notifyEvent(HealthEvent eventId, int param)
{
	if (_observerEvents.find(eventId) == _observerEvents.end())
	{
		return;
	}
	auto callbacks = _observerEvents[eventId];
	for (auto callback : callbacks)
	{
		callback(param);
	}
}

void Health::takeDamage(int amount)
{
	_currentHP = MAX(0, _currentHP - amount);
	notifyEvent(HealthEvent::OnTakeDamage, -amount);
	if (_currentHP == 0) notifyEvent(HealthEvent::OnDie, 0);
}


void Health::recovery(int amount)
{
	_currentHP = MIN(_maxHP, _currentHP + amount);
}

void Health::revive(int amount)
{
	amount = _maxHP - _currentHP;
	_currentHP = _maxHP;
	notifyEvent(HealthEvent::OnRevive, amount);
}
