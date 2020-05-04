#include "AudioManager.h"
#include <SDL_mixer.h>
#include <SDL.h>

AudioManager::AudioManager() : AudioManager(8) { }

AudioManager::AudioManager(int channels) : channels_(channels)
{
	if (SDL_Init(SDL_INIT_AUDIO) == 0)
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
			std::cout << "Audio Manager not loaded" << Mix_GetError() << std::endl;

	initialized_ = true;
}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
}

Mix_Chunk* AudioManager::loadSFX(const std::string& fileName)
{
	Mix_Chunk* sfx;
	sfx = Mix_LoadWAV(fileName.c_str());
	return sfx;
}

void AudioManager::playSFX(Mix_Chunk* sound, int loops, int channel)
{
	if (sound != nullptr && loops != -1)
		Mix_PlayChannel(channel, sound, loops);
}

Mix_Music* AudioManager::loadMusic(const std::string& fileName)
{
	Mix_Music* m = Mix_LoadMUS(fileName.c_str());
	return m;
}

void AudioManager::playMusic(Mix_Music* music, bool loops)
{
	if (music != nullptr) {
		Mix_PlayMusic(music, loops ? -1 : 0); //si loop= true se loopea(-1), en caso contrario 1 vez
	}
	else {
		//lanzar excepciones
	}
}

int AudioManager::setMusicVolume(int volume)
{
	return Mix_VolumeMusic(volume);
}


void AudioManager::pauseMusic()
{
	Mix_PauseMusic();
}

bool AudioManager::pausedMusic()
{
	return Mix_PausedMusic();
}

void AudioManager::resumeMusic()
{
	//silenced = false;
	Mix_ResumeMusic();
}

void AudioManager::resumeAll()
{
	//silenced = false;
	Mix_Resume(-1);
}

void AudioManager::stopMusic()
{
	//silenced = true;
	Mix_PauseMusic();
}

//void AudioManager::setGeneralVolume(float MaxVolume, float volume_ratio)
//{
//
//	Mix_Volume(-1, MaxVolume * volume_ratio);
//}

int AudioManager::setSFXVolume( int volume)
{
	return Mix_Volume(-1, volume);
}

/*int AudioManager::getGeneralVolume() const
{
	return Mix_Volume(-1, 1);
}*/

int AudioManager::getMusicVolume() const
{
	return Mix_VolumeMusic(-1);
}

int AudioManager::getSFXVolume() const
{
	return Mix_Volume(-1, -1);
}

