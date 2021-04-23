#include "Brick.h"

#include <string>

Brick::Brick(Shapes::Shape* shape, float x, float y, int level)
	: Body(shape, x, y, false), m_Level(level)
{
	
}

Brick::~Brick()
{
}

void Brick::init()
{
}

void Brick::onKeyboardDown(const SDL_Keycode& KC)
{
}
void Brick::onKeyboardUp(const SDL_Keycode& KC)
{
}

void Brick::update()
{
}