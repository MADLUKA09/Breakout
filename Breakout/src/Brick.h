#pragma once

#include "Engine/Body.h"
#include <string>

#include "SDL.h"

class Brick : public Body {
public:
	Brick(Shapes::Shape* shape, int x, int y, int level);
	~Brick();


protected:
	// From Entity
	virtual void init();
	virtual void onKeyboardDown(const SDL_Keycode& KC);
	virtual void onKeyboardUp(const SDL_Keycode& KC);
	virtual void update();

private:
	int			m_Level;
};
