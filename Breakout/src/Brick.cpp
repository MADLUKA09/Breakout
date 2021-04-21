#include "Brick.h"

#include <string>

Brick::Brick(Shapes::Shape* shape, int x, int y, int level)
	: Body(shape, x, y, false), m_Level(level)
{
	
}

Brick::~Brick()
{
}

void Brick::init()
{
}

void Brick::handleEvents()
{
}

void Brick::update()
{
}