#ifndef __OPTIONS_LAYER_H__
#define  __OPTIONS_LAYER_H__

#include "SwallowTouchLayer.h"

class OptionsLayer : public SwallowTouchLayer
{
public:
	virtual bool init();

	CREATE_FUNC(OptionsLayer);
protected:
	ui::Slider* _sfxSlider, * _bgmSlider;

	bool initContent();
};

#endif // !__OPTIONS_LAYER_H__
