#include "Brick.h"

#include <string>

Brick::Brick(int x, int y, int width, int height, int level, const std::string& texPath)
	: RigidBody(x, y, RB_Type::Rectangle), m_Level(level)
{
	m_Rectangle.w = width;
	m_Rectangle.h = height;
	m_Rectangle.x = x;
	m_Rectangle.y = y;

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
	m_Rectangle.x = getPosition().x;
	m_Rectangle.y = getPosition().y;
}

void Brick::render()
{
	SDL_RenderCopy(gm->getRenderer(), m_Texture, NULL, &m_Rectangle);
}

void Brick::onCollision(RigidBody* other) 
{
	
}