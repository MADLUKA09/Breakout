#include "GameManager.h"
#include <iostream>

#include "Entity.h"
#include "Body.h"

void GameManager::init(const char* title, int xPos, int yPos, int width, int height, int frameRate) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Log("SDL initialized...");

		m_Window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
		if (m_Window)
			SDL_Log("Window created...");
		
		m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		if (m_Renderer) {
			SDL_SetRenderDrawColor(m_Renderer, 127, 127, 127, 255);
			SDL_Log("Renderer created...");
		}

		if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096)) {
			SDL_Log("Audio init failed...");
		}

		m_FrameStart		= 0;
		m_FrameTime			= 0;
		m_TargetFramerate	= frameRate;
		m_TargetFrameTime	= 1000 / frameRate;

		m_WindowWidth = width;
		m_WindowHeight = height;

		m_textureManager	= new TextureManager(m_Renderer);
		m_CollisionManager	= new CollisionManager();
		m_Running			= true;
		SDL_Log("Initialization done!");
	}
	else {
		m_Running = false;
		SDL_Log("GM init failed!");
	}
}

void GameManager::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_Running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_Running = false;
			for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneEntities.begin(); it != m_SceneEntities.end(); ++it) {
				(*it)->entityOnKeyboardDown(event.key.keysym.sym);
			}
			for (std::vector<std::shared_ptr<Body>>::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
				(*it)->entityOnKeyboardDown(event.key.keysym.sym);
			}
			for (std::vector<std::shared_ptr<Body>>::iterator it = m_DynamicBodies.begin(); it != m_DynamicBodies.end(); ++it) {
				(*it)->entityOnKeyboardDown(event.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneEntities.begin(); it != m_SceneEntities.end(); ++it) {
				(*it)->entityOnKeyboardUp(event.key.keysym.sym);
			}
			for (std::vector<std::shared_ptr<Body>>::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
				(*it)->entityOnKeyboardUp(event.key.keysym.sym);
			}
			for (std::vector<std::shared_ptr<Body>>::iterator it = m_DynamicBodies.begin(); it != m_DynamicBodies.end(); ++it) {
				(*it)->entityOnKeyboardUp(event.key.keysym.sym);
			}
			break;
		}
	}
}

void GameManager::update() {

	m_CollisionManager->moveWithCollisions(m_DynamicBodies, m_StaticBodies, float(getFrameTime()));
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneEntities.begin(); it != m_SceneEntities.end(); ++it) {
		(*it)->entityUpdate();
	}
	for (std::vector<std::shared_ptr<Body>>::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
		(*it)->entityUpdate();
	}
	for (std::vector<std::shared_ptr<Body>>::iterator it = m_DynamicBodies.begin(); it != m_DynamicBodies.end(); ++it) {
		(*it)->entityUpdate();
	}


}

void GameManager::render() {
	SDL_SetRenderDrawColor(m_Renderer, 127, 127, 127, 255);
	SDL_RenderClear(m_Renderer);

	//Add stuff to render
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneEntities.begin(); it != m_SceneEntities.end(); ++it) {
		(*it)->entityRender();
	}
	for (std::vector<std::shared_ptr<Body>>::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
		(*it)->entityRender();
	}
	for (std::vector<std::shared_ptr<Body>>::iterator it = m_DynamicBodies.begin(); it != m_DynamicBodies.end(); ++it) {
		(*it)->entityRender();
	}
	
	SDL_RenderPresent(m_Renderer);
}

void GameManager::clean(){
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_Quit();
	SDL_Log("Game cleaned");
}

void GameManager::addSceneEntity(std::shared_ptr<Entity> newSceneObject) {
	m_SceneEntities.push_back(newSceneObject);
}

void GameManager::addSceneBody(std::shared_ptr<Body> newSceneBody) {
	if (newSceneBody->isDynamic())
		m_DynamicBodies.push_back(newSceneBody);
	else
		m_StaticBodies.push_back(newSceneBody);
}

void GameManager::removeInactiveObjects()
{
	bool erasedOne = false;
	for (BodyVector::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
		if (erasedOne == true) {
			--it;
			erasedOne = false;
		}
		if (!(*it)->isActive()) {
			it = m_StaticBodies.erase(it);
			if (it == m_StaticBodies.end())
				break;
			erasedOne = true;
		}
	}
}

void GameManager::removeBodiesByLayer(int layer)
{
	bool erasedOne = false;
	for (BodyVector::iterator it = m_StaticBodies.begin(); it != m_StaticBodies.end(); ++it) {
		if (erasedOne == true) {
			--it;
			erasedOne = false;
		}
		if ((*it)->getLayer() == layer) {
			it = m_StaticBodies.erase(it);
			if (it == m_StaticBodies.end())
				break;
			erasedOne = true;
		}
	}

	erasedOne = false;
	for (BodyVector::iterator it = m_DynamicBodies.begin(); it != m_DynamicBodies.end(); ++it) {
		if (erasedOne == true) {
			--it;
			erasedOne = false;
		}
		if ((*it)->getLayer() == layer) {
			it = m_DynamicBodies.erase(it);
			if (it == m_DynamicBodies.end())
				break;
			erasedOne = true;
		}
	}
}

void GameManager::startFrame() {
	m_FrameStart = SDL_GetTicks();
}

void GameManager::setFrameTime() {
	m_FrameTime = SDL_GetTicks() - m_FrameStart;
	if (m_TargetFrameTime > m_FrameTime) {
		SDL_Delay(m_TargetFrameTime - m_FrameTime);
		m_FrameTime = SDL_GetTicks() - m_FrameStart;
	}
	DEBUGINFO("Frame time: " << m_FrameTime << "ms")
}