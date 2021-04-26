#pragma once

#include "SDL.h"
#include "SDL_mixer.h"

#include <vector>
#include <memory>
#include <bitset>
#include "TextureManager.h"
#include "CollisionManager.h"

class Entity;
class Body;

using EntityVector = std::vector<std::shared_ptr<Entity>>;
using BodyVector = std::vector<std::shared_ptr<Body>>;

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
	void addSceneBody(std::shared_ptr<Body> newSceneBody);
	void destroyInactiveSceneObjects();
	void addDynamic(std::shared_ptr<Body> body);
	void addStatic(std::shared_ptr<Body> body);
	void removeDynamic(std::shared_ptr<Body> body);
	void removeStatic(std::shared_ptr<Body> body);
	void cleanAllObjects() {
		m_SceneObjects.clear();
		m_StaticBodies = BodyVector();
		m_DynamicBodies = BodyVector();
	}
	

	SDL_Renderer* getRenderer() { return m_Renderer; }

	// Textures
	SDL_Texture*	getTexture(const std::string& name) { return m_textureManager->getTexture(name); }
	void			addTexture(const std::string& name, const std::string& path) { m_textureManager->loadTexture(name, path); }

	// Frame timing
	void	startFrame();
	void	setFrameTime();
	int		getFrameTime() { return m_FrameTime; }

	// Window
	constexpr int getWindowWidth() { return m_WindowWidth; }
	constexpr int getWindowHeight() { return m_WindowHeight; }

private:
	GameManager() {}

	bool m_Running;

	SDL_Window*		m_Window;
	SDL_Renderer*	m_Renderer;

	TextureManager* m_textureManager;
	CollisionManager* m_CollisionManager;

	EntityVector m_SceneObjects;
	BodyVector m_SceneBodies;
	BodyVector m_DynamicBodies;
	BodyVector m_StaticBodies;


	// Frame timing members
	Uint32	m_FrameStart;
	int		m_FrameTime;
	int		m_TargetFramerate;
	int		m_TargetFrameTime;

	// Window
	int m_WindowWidth;
	int m_WindowHeight;

};

