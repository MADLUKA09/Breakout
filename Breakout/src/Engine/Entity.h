#pragma once

#include "SDL.h"

#include <memory>

#include "GameManager.h"
#include "SimpleVector2.h"

#define FRAMETIME float(gm->getFrameTime())
#define WINDOWWIDTH gm->getWindowWidth()
#define WINDOWHEIGHT gm->getWindowHeight()

using SubObjectVector = std::vector<std::shared_ptr<Entity>>;

class Entity {
public:
	Entity();
	Entity(float x, float y, std::shared_ptr<Entity> parent = nullptr);
	~Entity();

	void entityInit();
	void entityOnKeyboardDown(const SDL_Keycode& KC);
	void entityOnKeyboardUp(const SDL_Keycode& KC);
	void entityUpdate();
	void entityRender();
	virtual void entityCollision() {}

	bool isActive() { return m_Active; }
	void setActive(bool b) { m_Active = b; }
	void addSubObject(std::shared_ptr<Entity> ent);
	void removeSubobject(std::shared_ptr<Entity> ent);
	void destroyInactiveSubobjects();
	void destroy();

	SimpleVector2<float> getPosition()		{ return m_Position; }

	void setPosition(float x, float y)		{ m_Position.x = x; m_Position.y = y; }
	
	static void setGameManager(GameManager* _gm) { gm = _gm; }
	static GameManager* getGameManager() { return gm; }

	std::shared_ptr<Entity> getParent() { return m_Parent; }
	SubObjectVector m_SubObjects;
protected:
	virtual void bodyMove() {}
	virtual void bodyUpdate() {}
	virtual void bodyCollision() {}
	virtual void bodyDestroy() {}

	virtual void init()				{}
	virtual void onKeyboardDown(const SDL_Keycode& keyCode)	{}
	virtual void onKeyboardUp(const SDL_Keycode& keyCode)	{}
	virtual void update()			{}
	virtual void render()			{}

	//Every entity has a pointer to the game manager object
	static GameManager* gm;

private:
	bool m_Active;
	SimpleVector2<float> m_Position;

	std::shared_ptr<Entity> m_Parent;
};