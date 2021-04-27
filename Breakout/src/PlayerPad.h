#pragma once
#include <string>

#include "Engine/Body.h"
#include "Engine/SimpleVector2.h"

#include "Ball.h"

class PlayerPad : public Body
{
public:
	PlayerPad(Shapes::Shape* shape, float x, float y, std::shared_ptr<Ball> startingBall);

	virtual void onCollision(std::shared_ptr<Body> other);
	int getPoints() { return m_Points; }
	void addPoints(int points) { m_Points += points; }

protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& keyCode);
	virtual void onKeyboardUp(const SDL_Keycode& keyCode);
	virtual void update();

private:
	int m_Points = 0;

	int bounceCount = 0;
	std::shared_ptr<Ball> m_StartingBall;

};

