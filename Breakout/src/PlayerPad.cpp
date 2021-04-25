#include "PlayerPad.h"

PlayerPad::PlayerPad(Shapes::Shape* shape, float x, float y, std::shared_ptr<Ball> ball)
	: Body(shape, x, y, true), m_StartingBall (ball)
{
	m_Launched = false;
	setMaxSpeed(0.1f);
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
		setAcceleration(- 0.005f, 0.f);
		break;
	case SDLK_RIGHT:
		setAcceleration(0.005f, 0.f);
		break;
	case SDLK_SPACE:
		if (!m_Launched) {
			m_StartingBall->releaseWithSpeed(SimpleVector2<float>(0.12f, 0.12f));
			m_Launched = true;
		}
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

	/*if (!m_Launched) {
		static int ballWidth = m_StartingBall->getShapeWidth();
		static int padWidth = this->getShapeWidth();
		static int padHeight = this->getShapeHeight();

		SimpleVector2<float> thisPos = this->getPosition();
		m_StartingBall->setPosition(thisPos.x + padWidth / 2 - ballWidth / 2,
			thisPos.y - ballWidth / 2 - 460);
	}*/
}