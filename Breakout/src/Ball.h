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
	~Ball();

	void releaseWithSpeed(SimpleVector2<float> speed);

protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& KC);
	virtual void onKeyboardUp(const SDL_Keycode& KC);
	virtual void update();

};

