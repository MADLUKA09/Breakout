#pragma once

#include "SDL.h"

#include <memory>

#include "GameManager.h"
#include "SimpleVector2.h"

class Entity {
public:
	Entity();
	Entity(int x, int y);

	void entityInit();
	void entityHandleEvents();
	void entityUpdate();
	void entityRender();

	SDL_Point getPosition()				{ return m_Position; }
	SimpleVector2<int> getVelocity()	{ return m_Velocity; }


	void setPosition(int x, int y) { m_Position.x = x; m_Position.y = y; }
	void setVelocity(SimpleVector2<int> vector) { m_Velocity = vector; }
	void setVelocityX(int _x) { m_Velocity.x = _x; }
	void setVelocityY(int _y) { m_Velocity.y = _y; }

	static void setGameManager(GameManager* _gm) { gm = _gm; }
	static GameManager* getGameManager() { return gm; }


protected:
	virtual void bodyUpdate() {}

	virtual void init() {}
	virtual void handleEvents() {}
	virtual void update() {}
	virtual void render() {}

	//Every entity has a pointer to the game manager object
	static GameManager* gm;

private:
	bool m_Active;
	SDL_Point m_Position;
	SimpleVector2<int> m_Velocity;

	void moveByVelocity();

};