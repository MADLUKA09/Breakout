#pragma once

#include "Engine/Body.h"
#include <string>

struct Circle {
	int x, y; // Center of the circle
	int radius;
};

class Ball : public Body
{
public:
	Ball(Shapes::Shape* shape, float x, float y);

	void releaseWithSpeed(SimpleVector2<float> speed);
	virtual void onCollision(std::shared_ptr<Body> other) {}
	bool hasLaunched() { return m_Launched; }
	void setLaunched(bool launch) { m_Launched = launch; }
	void speedUp() { m_Speed += 0.05f; }
	float getSpeed() { return m_Speed; }

protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& KC);
	virtual void onKeyboardUp(const SDL_Keycode& KC);
	virtual void update();

private:
	bool m_Launched = false;
	float m_Speed = 0.2f;

};

