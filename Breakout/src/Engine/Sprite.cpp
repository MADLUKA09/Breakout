#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, int width, int height)
	: m_Texture (texture)
{
	m_DestRectangle.w = width;
	m_DestRectangle.h = height;
}

void Sprite::draw(SDL_Renderer* renderer, int x, int y) {
	m_DestRectangle.x = x;
	m_DestRectangle.y = y;
	SDL_RenderCopy(renderer, m_Texture, NULL, &m_DestRectangle);
}