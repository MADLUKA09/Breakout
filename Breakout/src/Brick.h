#pragma once

#include "Engine/Body.h"
#include "Engine/SoundEffect.h"
#include <string>
#include "SDL.h"

#include "BrickType.h"

class Brick : public Body {
public:
	Brick(Shapes::Shape* shape, float x, float y, BrickType brickType, std::shared_ptr<Entity> parent = nullptr);
	~Brick(){}

	virtual void onCollision(std::shared_ptr<Body> other);
	void addSound(std::string soundName);

protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& KC);
	virtual void onKeyboardUp(const SDL_Keycode& KC);
	virtual void update();

private:
	bool		m_Breakable;
	int			m_HitPoints;
	int			m_BreakScore;

	SoundEffect m_SoundEffectHit;
	SoundEffect m_SoundEffectBreak;
};
