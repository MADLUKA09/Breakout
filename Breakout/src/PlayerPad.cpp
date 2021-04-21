#include "PlayerPad.h"

PlayerPad::PlayerPad(Shapes::Shape* shape, int x, int y)
	: Body(shape, x, y, true)
{

}

PlayerPad::~PlayerPad() {}

void PlayerPad::init()
{
}

void PlayerPad::handleEvents() 
{
	setVelocityX(0);
	bool leftPressed = gm->getControls()->isPressed(CONT_LEFT);
	bool rightPressed = gm->getControls()->isPressed(CONT_RIGHT);
	if (leftPressed && rightPressed)
		return;

	if (rightPressed) {
		setVelocityX(3);
	}

	if (leftPressed) {
		setVelocityX(-3);
	}
}

void PlayerPad::update()
{
	setPosition(getPosition().x + getVelocity().x, getPosition().y);
}