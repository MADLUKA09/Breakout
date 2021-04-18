#pragma once

#include "SDL.h"

#include <vector>
#include <memory>

class Entity;

//GameManager singleton, contains everything in the game
class GameManager
{
public:
	GameManager(const GameManager& ) = delete;

	static GameManager* Get() {
		static GameManager* gm = new GameManager();
		return gm;
	}

	void init(const char* title, int xPos, int yPos, int width, int height);
	void handleEvents();
	void update();
	void render();
	void clean();

	void addSceneObject(std::shared_ptr<Entity> newSceneObject);

	SDL_Renderer* getRenderer() { return m_Renderer; }

	bool isRunning() { return m_Running; }
private:
	GameManager() {}

	SDL_Window*		m_Window;
	SDL_Renderer*	m_Renderer;
	
	std::vector<std::shared_ptr<Entity>> m_SceneObjects;

	bool m_Running;
};

