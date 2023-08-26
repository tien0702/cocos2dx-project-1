#include "AudioManager.h"
#include "GameConfig.h"
#include "Utilities/DefaultPath.h"

AudioManager* AudioManager::_instance;

AudioManager* AudioManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new AudioManager();
	}

	return _instance;
}

void AudioManager::playBGM(std::string audioName)
{
	_currentBackgroundID = AudioEngine::play2d(audioName, true, GameConfig::_bgmVolume);
}

void AudioManager::playSFX(std::string audioName)
{
	int id = AudioEngine::play2d(audioName, false, GameConfig::_sfxVolume);
	/*if (_audioCache.find(audioName) == _audioCache.end())
	{
		int id = AudioEngine::play2d(audioName, false, GameConfig::_sfxVolume);
		_audioCache.insert(std::pair<std::string, int>(audioName, id));
	}
	else
	{
		if (AudioEngine::getState(_audioCache[audioName]) == AudioEngine::AudioState::PLAYING) return;
		_audioCache[audioName] = AudioEngine::play2d(audioName, false, GameConfig::_sfxVolume);
	}*/
}

void AudioManager::pausBGM()
{
	AudioEngine::pause(_currentBackgroundID);
}

void AudioManager::stopBGM()
{
	AudioEngine::stop(_currentBackgroundID);
}

void AudioManager::resumBGM()
{
	AudioEngine::resume(_currentBackgroundID);
}

void AudioManager::onClickBtn()
{
	playSFX(DefaultPath::AUDIO_PATH + "Button.mp3");
}

void AudioManager::setVolumeBGM(float val)
{
	GameConfig::_bgmVolume = val;
	AudioEngine::setVolume(_currentBackgroundID, GameConfig::_bgmVolume);
}

void AudioManager::setVolumeSFX(float val)
{
	GameConfig::_sfxVolume = val;
}
