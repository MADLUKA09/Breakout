#pragma once
#include <string>

#include "Engine/Body.h"
#include "Engine/SimpleVector2.h"

class PlayerPad : public Body
{
public:
	PlayerPad(Shapes::Shape* shape, int x, int y);
	~PlayerPad();

protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& keyCode);
	virtual void onKeyboardUp(const SDL_Keycode& keyCode);
	virtual void update();
};

