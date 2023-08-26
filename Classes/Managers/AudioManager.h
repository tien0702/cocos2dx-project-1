#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "cocos/audio/include/AudioEngine.h"

USING_NS_CC;

class AudioManager
{
public:
	static AudioManager* getInstance();
	void playBGM(std::string audioName);
	void playSFX(std::string audioName);
	void pausBGM();
	void stopBGM();
	void resumBGM();
	void onClickBtn();

	void setVolumeBGM(float val);
	void setVolumeSFX(float val);

protected:
	static AudioManager* _instance;
	
	int _currentBackgroundID;

	std::map<std::string, int> _audioCache;
};

#endif // !__AUDIO_MANAGER_H__
