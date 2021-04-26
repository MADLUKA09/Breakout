#include "Brick.h"

Brick::Brick(Shapes::Shape* shape, float x, float y, LEVEL::BrickType bt)
	: Body(shape, x, y, false)
{

	m_HitPoints = bt.hitPoints;
	m_BreakScore = bt.breakScore;
	applyTexture(bt.texture);
	m_SoundEffectHit = bt.hitSound;
	m_SoundEffectBreak = bt.breakSound;
	
}

Brick::~Brick()
{
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
	m_SoundEffectHit.playSound();
}

void Brick::addSound(std::string soundName)
{
	m_SoundEffectHit.loadSound(soundName);
}
