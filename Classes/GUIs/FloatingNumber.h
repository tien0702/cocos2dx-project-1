#ifndef __FLOATING_NUMBER_H__
#define __FLOATING_NUMBER_H__

#include "GameConfig.h"

#include "cocos2d.h"

USING_NS_CC;

class FloatingNumber
{
public:
	static FloatingNumber* getIns();
public:
	void floatText(Vec2 position, std::string content, Color4B color);
private:
	TTFConfig _font;
	Sequence* _zoom;
	static FloatingNumber* _instance;
	FloatingNumber();
};

#endif // !__FLOATING_NUMBER_H__
