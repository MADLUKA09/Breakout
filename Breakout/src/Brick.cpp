#include "Brick.h"

std::shared_ptr<Level> Brick::m_Level;

Brick::Brick(Shapes::Shape* shape, float x, float y, BrickType bt)
	: Body(shape, x, y, false)
{

	m_HitPoints = bt.hitPoints;
	m_BreakScore = bt.breakScore;
	applyTexture(bt.texture);
	m_SoundEffectHit = bt.hitSound;
	m_SoundEffectBreak = bt.breakSound;
	
	m_Breakable = bt.breakable;
	if (!m_Breakable)
		m_HitPoints = 1;
}


void Brick::init()
{
}

void Brick::onKeyboardDown(const SDL_Keycode& KC)
{
}
void Brick::onKeyboardUp(const SDL_Keycode& KC)
{
}

void Brick::update()
{
}

void Brick::onCollision(std::shared_ptr<Body> other) {
	if (m_Breakable)
		--m_HitPoints;
	if (m_HitPoints <= 0) {
		m_Level->decrementBricks();
		setActive(false);
		m_SoundEffectBreak.playSound();
	}
	else m_SoundEffectHit.playSound();
}

void Brick::addSound(std::string soundName)
{
	m_SoundEffectHit.loadSound(soundName);
}
