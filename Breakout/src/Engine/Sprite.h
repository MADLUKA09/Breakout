#pragma once

#include "SDL.h"
#include <string>
#include "Entity.h"

class Sprite
{
public:
	Sprite(SDL_Texture* texture, int width, int height);

	void draw(SDL_Renderer* renderer, int x, int y);
	int getWidth() { return m_DestRectangle.w; }
	int getHeight() { return m_DestRectangle.w; }

private:
	SDL_Texture* m_Texture;
	SDL_Rect	 m_DestRectangle;

	static SDL_Renderer* m_Renderer;
};

