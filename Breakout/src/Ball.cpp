#include "Ball.h"

Ball::Ball(Shapes::Shape* shape, float x, float y)
	: Body(shape, x, y, true)
{
	setFriction(0.f);
	setActive(true);
}

void Ball::init()
{
	m_Launched = false;
	m_Speed = 0.2f;
	setActive (true);
}

void Ball::onKeyboardDown(const SDL_Keycode& KC)
{
}
void Ball::onKeyboardUp(const SDL_Keycode& KC)
{
}

void Ball::update()
{

}

void Ball::releaseWithSpeed(SimpleVector2<float> speed) {
	this->setVelocity(speed.x, speed.y);
}