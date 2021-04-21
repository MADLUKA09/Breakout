#include "GameManager.h"
#include <iostream>

#include "Entity.h"

void handleKeyDownEvent(GameManager* gm, SDL_Scancode keyCode);
void handleKeyUpEvent(GameManager* gm, SDL_Scancode keyCode);

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

		m_FrameStart		= 0;
		m_FrameTime			= 0;
		m_TargetFramerate	= frameRate;
		m_TargetFrameTime	= 1000 / frameRate;

		m_textureManager	= new TextureManager(m_Renderer);
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
			std::cout << "key pressed: " << std::flush;
			handleKeyDownEvent(this, event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			handleKeyUpEvent(this, event.key.keysym.scancode);
			break;
		}
	}

	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneObjects.begin(); it != m_SceneObjects.end(); ++it) {
		(*it)->entityHandleEvents();
	}
}

void GameManager::update() {
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneObjects.begin(); it != m_SceneObjects.end(); ++it) {
		(*it)->entityUpdate();
	}
}

void GameManager::render() {
	SDL_SetRenderDrawColor(m_Renderer, 127, 127, 127, 255);
	SDL_RenderClear(m_Renderer);

	//Add stuff to render
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneObjects.begin(); it != m_SceneObjects.end(); ++it) {
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

void GameManager::addSceneObject(std::shared_ptr<Entity> newSceneObject) {
	m_SceneObjects.push_back(newSceneObject);
}

void GameManager::addDynamic(std::shared_ptr<Body> body) {
	dynamicBodies.push_back(body);
}

void GameManager::addStatic(std::shared_ptr<Body> body) {
	staticBodies.push_back(body);
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
	std::cout << "Frame time: " << m_FrameTime << "ms" << std::endl;
}

void handleKeyDownEvent(GameManager* gm, SDL_Scancode keyCode) {
	switch (keyCode) {
	case SDL_SCANCODE_LEFT:
		std::cout << "LEFT" << std::endl;
		gm->getControls()->setPressed(CONT_LEFT);
		break;
	case SDL_SCANCODE_RIGHT:
		std::cout << "RIGHT" << std::endl;
		gm->getControls()->setPressed(CONT_RIGHT);
		break;
	case SDL_SCANCODE_SPACE:
		gm->getControls()->setPressed(CONT_SPACE);
		break;
	}
}

void handleKeyUpEvent(GameManager* gm, SDL_Scancode keyCode) {
	switch (keyCode) {
	case SDL_SCANCODE_LEFT:
		gm->getControls()->setReleased(CONT_LEFT);
		break;
	case SDL_SCANCODE_RIGHT:
		gm->getControls()->setReleased(CONT_RIGHT);
		break;
	case SDL_SCANCODE_SPACE:
		gm->getControls()->setReleased(CONT_SPACE);
		break;
	}
}