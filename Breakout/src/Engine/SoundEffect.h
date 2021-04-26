#pragma once

#include "SDL_mixer.h"
#include <string>

class SoundEffect
{
public:
	SoundEffect();
	void loadSound(const std::string& soundName);
	void playSound();

private:
	Mix_Chunk* m_Sound;
};

