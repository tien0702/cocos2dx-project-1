#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "cocos2d.h"

USING_NS_CC;

class Utilities
{
public:
	static std::string justifyStrings(const std::string& str1, const std::string& str2, int width);
	// return <Animation*, NumberFrames>
	static std::pair<Animation*, int> createAnimation(std::string fileName);
	static Animation* createAnimation(std::string fileName, int numberFrames, float duration);
	static std::pair<std::string, std::string> initSpriteFramesPath(std::string path, std::string fileName);
};

#endif // !__UTILITIES_H__
