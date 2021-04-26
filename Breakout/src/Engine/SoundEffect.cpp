#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect()
{
}

void SoundEffect::loadSound(const std::string& soundName) {
	m_Sound = Mix_LoadWAV(soundName.c_str());

	if (m_Sound == nullptr) {
		std::cout << "Failed to load: " << soundName << std::endl;
	}
}

void SoundEffect::playSound()
{
	Mix_PlayChannel(-1, m_Sound, 0);
}
