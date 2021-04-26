#pragma once

#include "Engine/Body.h"
#include "Engine/SoundEffect.h"
#include <string>
#include "SDL.h"

#include "BrickType.h"
#include "Level.h"

class Brick : public Body {
public:
	Brick(Shapes::Shape* shape, float x, float y, BrickType brickType);
	~Brick(){}

	virtual void onCollision(std::shared_ptr<Body> other);
	void addSound(std::string soundName);

	static void setLvl(std::shared_ptr<Level> level) { m_Level = level; }
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

	static std::shared_ptr<Level> m_Level;
};
