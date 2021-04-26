#pragma once

#include "Engine/Body.h"
#include "Engine/SoundEffect.h"
#include "Level.h"
#include <string>

#include "SDL.h"

class Brick : public Body {
public:
	Brick(Shapes::Shape* shape, float x, float y, LEVEL::BrickType brickType);
	~Brick();

	virtual void onCollision(std::shared_ptr<Body> other);
	void addSound(std::string soundName);


protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& KC);
	virtual void onKeyboardUp(const SDL_Keycode& KC);
	virtual void update();

private:
	int			m_HitPoints;
	int			m_BreakScore;

	SoundEffect m_SoundEffectHit;
	SoundEffect m_SoundEffectBreak;
};
