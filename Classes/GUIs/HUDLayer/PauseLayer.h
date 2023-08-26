#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class PauseLayer : public LayerColor
{
public:
	virtual bool init();

	CREATE_FUNC(PauseLayer);
protected:

	ui::Slider* _sfxSlider, * _bgmSlider;

	bool initContent();
};

#endif // !__PAUSE_LAYER_H__
