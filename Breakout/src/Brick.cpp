#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int level, SDL_Color color)
	: Entity(x, y), m_Level(level), m_Color(color)
{
	m_Rectangle.w = width;
	m_Rectangle.h = height;
}

Brick::~Brick()
{
}

void Brick::init()
{
	m_Color.r = 0;
	m_Color.g = 255;
	m_Color.b = 255;
	m_Color.a = 255;
}

void Brick::handleEvents()
{
}

void Brick::update()
{
	m_Rectangle.x = getPosition().x;
	m_Rectangle.y = getPosition().y;
}

void Brick::render()
{
	SDL_SetRenderDrawColor(gm->getRenderer(), RGBA(m_Color));
	SDL_RenderFillRect(gm->getRenderer(), &m_Rectangle);
}