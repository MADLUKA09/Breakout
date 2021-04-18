#pragma once

#include "SDL.h"

#include <memory>

#include "GameManager.h"

#define RGBA(x) x.r, x.g, x.b, x.a

class Entity {
public:
	Entity();
	Entity(int x, int y);

	void entityInit();
	void entityUpdate();
	void entityRender();

	SDL_Point getPosition() { return m_Position; }

	static void setGameManager(GameManager* _gm) { gm = _gm; }

protected:
	virtual void init() {}
	virtual void update() {}
	virtual void render() {}

	//Every entity has a pointer to the game manager object
	static GameManager* gm;

private:
	SDL_Point m_Position;

};