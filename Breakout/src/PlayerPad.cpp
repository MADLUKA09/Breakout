#include "PlayerPad.h"

PlayerPad::PlayerPad(Shapes::Shape* shape, float x, float y, std::shared_ptr<Ball> ball)
	: Body(shape, x, y, true), m_StartingBall (ball)
{
	m_Launched = false;
	setMaxSpeed(0.4f);
}

void PlayerPad::init()
{
	setPosition(48.f, 568.f);
	m_Launched = false;
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
			m_StartingBall->releaseWithSpeed(SimpleVector2<float>(0.0f, -0.2f));
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
	if (getPosition().x < 5.1f) {
		setPosition(5.1f, getPosition().y);
		setVelocity(0.f, 0.f);
	}
	else if (getPosition().x > WINDOWWIDTH - getShapeWidth() - 5.1f) {
		setPosition(float(WINDOWWIDTH - getShapeWidth() - 5.1f), getPosition().y);
		setVelocity(0.f, 0.f);
	}

	if (!m_Launched) {
		static int ballWidth = m_StartingBall->getShapeWidth();
		static int padWidth = this->getShapeWidth();
		static int padHeight = this->getShapeHeight();

		SimpleVector2<float> thisPos = this->getPosition();
		m_StartingBall->setPosition(thisPos.x + padWidth / 2 - ballWidth / 2,
			thisPos.y - ballWidth / 2 - 20);
	}
}

void PlayerPad::onCollision(std::shared_ptr<Body> other) {
	static std::vector<float> speedUps = { 0.2f, 0.4f, 0.6f, 0.7f, 0.8f };
	if (other->isDynamic()) {
		++bounceCount;
		auto vel = speedUps[bounceCount / 5]; // Speed up every 5 bounces
		float relativeImpact = ((other->getPosition().x + other->getShapeWidth()/2) - (this->getPosition().x + this->getShapeWidth()/2))/this->getShapeWidth();
		SimpleVector2<float> direction(relativeImpact, -1.f);
		other->setVelocity(direction.normalized() * vel); 
	}
}