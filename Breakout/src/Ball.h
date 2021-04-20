#pragma once

#include "Engine/RigidBody.h"
#include <string>

struct Circle {
	int x, y; // Center of the circle
	int radius;
};

class Ball : public RigidBody
{
public:
	Ball(int x, int y, int radius, std::string texPath);
	~Ball();

protected:
	// From Entity
	virtual void init();
	virtual void handleEvents();
	virtual void update();
	virtual void render();

	// From RigidBody
	virtual void onCollision(RigidBody* other);

private:
	Circle			m_Circle;
	SDL_Texture*	m_Texture;
	SDL_Rect		m_Rectangle; // Needed for applying texture
};

