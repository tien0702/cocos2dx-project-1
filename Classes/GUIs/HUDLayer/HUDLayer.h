#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"

USING_NS_CC;

class HUDLayer : public Layer
{
public:
	static HUDLayer* getInstance();

protected:
	static HUDLayer* _instance;
	virtual bool init();
protected:
	void pauseCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	virtual void onEnter();
	virtual void update(float dt);
	virtual void onExit();
	virtual void resume();
protected:
	Camera* _mainCam;
	PauseLayer* _pauseLayer;
	bool _showingPauseLayer = false;

	Label* _enemiesKilledText, * _scoreText, * _timerText;
};

#endif // !__HUD_LAYER_H__
