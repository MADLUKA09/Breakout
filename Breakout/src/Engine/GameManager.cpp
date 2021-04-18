#include "GameManager.h"
#include "Entity.h"

void GameManager::init(const char* title, const int xPos, const int yPos, const int width, const int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Log("SDL initialized...");

		m_Window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
		if (m_Window)
			SDL_Log("Window created...");
		
		m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		if (m_Renderer) {
			SDL_SetRenderDrawColor(m_Renderer, 192, 255, 0, 255); //I like lime color
			SDL_Log("Renderer created...");
		}

		m_Running = true;

		SDL_Log("Initialization done!");
	}
	else {
		m_Running = false;
		SDL_Log("Init failed!");
	}
}

void GameManager::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		m_Running = false;
		break;
	}
}

void GameManager::update() {
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneObjects.begin(); it != m_SceneObjects.end(); ++it) {
		(*it)->entityUpdate();
	}
}

void GameManager::render() {
	SDL_SetRenderDrawColor(m_Renderer, 192, 255, 0, 255);
	SDL_RenderClear(m_Renderer);
	for (std::vector<std::shared_ptr<Entity>>::iterator it = m_SceneObjects.begin(); it != m_SceneObjects.end(); ++it) {
		(*it)->entityRender();
	}
	//Add stuff to render
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