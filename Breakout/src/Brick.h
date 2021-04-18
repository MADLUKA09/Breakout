#pragma once

#include "Engine/Entity.h"
#include "SDL.h"

class Brick : public Entity {
public:
	Brick(int x, int y, int width, int height, int level, SDL_Color color);
	~Brick();

	void handleEvents();

protected:
	virtual void init();
	virtual void update();
	virtual void render();

private:
	int			m_Level;

	SDL_Rect	m_Rectangle;
	SDL_Color	m_Color;
};
