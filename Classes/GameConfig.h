#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

class GameConfig
{
public:
	static std::string _path;
	static float _sfxVolume;
	static float _bgmVolume;

	static bool save();
	static bool load();
};


#endif // !__GAME_CONFIG_H__
