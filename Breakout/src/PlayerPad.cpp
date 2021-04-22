#include "PlayerPad.h"

PlayerPad::PlayerPad(Shapes::Shape* shape, int x, int y)
	: Body(shape, x, y, true)
{
}

PlayerPad::~PlayerPad() {}

void PlayerPad::init()
{
}

void PlayerPad::onKeyboardDown(const SDL_Keycode& KC)
{
	static float maxAcceleration = 3.f;
	switch (KC) {
	case SDLK_LEFT:
		setAcceleration(- 5.f, 0.f);
		break;
	case SDLK_RIGHT:
		setAcceleration(5.f, 0.f);
		break;
	}
}

void PlayerPad::onKeyboardUp(const SDL_Keycode& KC)
{
	switch (KC) {
	case SDLK_LEFT:
		setAcceleration(0.f, 0.f);
		break;
	case SDLK_RIGHT:
		setAcceleration(0.f, 0.f);
		break;
	}
}

void PlayerPad::update()
{
	if (getPosition().x < 1.f) {
		setPosition(1.1f, getPosition().y);
		setVelocity(0.f, 0.f);
	}
	else if (getPosition().x > WINDOWWIDTH - getShapeWidth()) {
		setPosition(float(WINDOWWIDTH - getShapeWidth()), getPosition().y);
		setVelocity(0.f, 0.f);
	}
}