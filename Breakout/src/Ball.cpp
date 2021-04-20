#include "Ball.h"

Ball::Ball(int x, int y, int radius, std::string texPath)
	: RigidBody(x, y, RB_Type::Circle)
{
	m_Circle.x = x;
	m_Circle.y = y;
	m_Circle.radius = radius;

	m_Rectangle.w = m_Rectangle.h = 2 * radius;
	m_Rectangle.x = x+radius;
	m_Rectangle.y = y+radius;

	m_Texture = NULL;

	SDL_Surface* surface = SDL_LoadBMP(texPath.c_str());

	if (surface == NULL)
		SDL_Log("Failed to load image!");
	else {
		m_Texture = SDL_CreateTextureFromSurface(gm->getRenderer(), surface);
		if (m_Texture == NULL)
			SDL_Log("Failed to create texture from surface!");
	}

	SDL_FreeSurface(surface);
}

Ball::~Ball()
{
}

void Ball::init()
{
}

void Ball::handleEvents()
{
}

void Ball::update()
{
	m_Circle.x = getPosition().x;
	m_Circle.y = getPosition().y;

	m_Rectangle.x = m_Circle.x + m_Circle.radius;
	m_Rectangle.y = m_Circle.y + m_Circle.radius;;
}

void Ball::render()
{
	SDL_RenderCopy(gm->getRenderer(), m_Texture, NULL, &m_Rectangle);
}

void Ball::onCollision(RigidBody* other)
{

}