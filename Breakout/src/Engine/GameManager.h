#pragma once

#include "SDL.h"

#include <vector>
#include <memory>
#include <bitset>
#include "TextureManager.h"

#define CONT_LEFT 0
#define CONT_RIGHT 1
#define CONT_SPACE 2

class Entity;
class Body;

struct controls {
public:
	bool isPressed(int i) { return controlsPressed[i]; }
	void setPressed(int i) { controlsPressed[i] = 1; }
	void setReleased(int i) { controlsPressed[i] = 0; }

private:
	std::bitset<3> controlsPressed;
};

//GameManager singleton, contains everything in the game
class GameManager
{
public:
	GameManager(const GameManager& ) = delete;

	static GameManager* Get() {
		static GameManager* gm = new GameManager();
		return gm;
	}

	void init(const char* title, int xPos, int yPos, int width, int height, int frameRate = 60);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning() { return m_Running; }
	void addSceneObject(std::shared_ptr<Entity> newSceneObject);
	void addDynamic(std::shared_ptr<Body> body);
	void addStatic(std::shared_ptr<Body> body);

	SDL_Renderer* getRenderer() { return m_Renderer; }
	controls* getControls() { return &m_Controls; }

	// Textures
	SDL_Texture*	getTexture(const std::string& name) { return m_textureManager->getTexture(name); }
	void			addTexture(const std::string& name, const std::string& path) { m_textureManager->loadTexture(name, path); }

	// Frame timing
	void	startFrame();
	void	setFrameTime();
	int		getFrameTime() { return m_FrameTime; }

private:
	GameManager() {}

	bool m_Running;

	SDL_Window*		m_Window;
	SDL_Renderer*	m_Renderer;

	TextureManager* m_textureManager;

	std::vector<std::shared_ptr<Entity>> m_SceneObjects;
	std::vector<std::shared_ptr<Body>> dynamicBodies;
	std::vector<std::shared_ptr<Body>> staticBodies;

	controls m_Controls;

	// Frame timing members
	Uint32	m_FrameStart;
	int		m_FrameTime;
	int		m_TargetFramerate;
	int		m_TargetFrameTime;

};

