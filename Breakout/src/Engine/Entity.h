#pragma once

#include "SDL.h"

#include <memory>

#include "GameManager.h"
#include "SimpleVector2.h"

#define FRAMETIME float(gm->getFrameTime())
#define WINDOWWIDTH gm->getWindowWidth()
#define WINDOWHEIGHT gm->getWindowHeight()

class IDType {
private:
	int IDnumber;

public:
	IDType() {
		assignID();
	}

	int getIDNumber() const { return IDnumber; }

	bool operator==(const IDType& other) const {
		if (this->IDnumber == other.getIDNumber())
			return true;
		else return false;
	}

private:

	void assignID() {
		IDnumber = getID();
	}

	static int getID() {
		static int idnr = 1;
		return idnr++;
	}

};

class Entity {
public:
	Entity();
	Entity(float x, float y);
	~Entity();

	IDType& getID() const { return m_ID; }

	void entityInit();
	void entityOnKeyboardDown(const SDL_Keycode& KC);
	void entityOnKeyboardUp(const SDL_Keycode& KC);
	void entityUpdate();
	void entityRender();

	bool isActive() { return m_Active; }
	void setActive(bool b) { m_Active = b; }
	void destroy();

	SimpleVector2<float> getPosition()		{ return m_Position; }

	void setPosition(float x, float y)		{ m_Position.x = x; m_Position.y = y; }
	
	static void setGameManager(GameManager* _gm) { gm = _gm; }
	static GameManager* getGameManager() { return gm; }

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
	IDType m_ID;
	bool m_Active;
	SimpleVector2<float> m_Position;
};