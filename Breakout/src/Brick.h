#pragma once

#include "Engine/RigidBody.h"
#include <string>

#include "SDL.h"

class Brick : public RigidBody {
public:
	Brick(int x, int y, int width, int height, int level, const std::string& texPath);
	~Brick();


protected:
	// From Entity
	virtual void init();
	virtual void handleEvents();
	virtual void update();
	virtual void render();

	// From RigidBody
	virtual void onCollision(RigidBody* other);

private:
	int			m_Level;

	SDL_Rect	m_Rectangle;

	SDL_Texture* m_Texture;
};