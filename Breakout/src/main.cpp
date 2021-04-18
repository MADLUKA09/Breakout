#include <stdio.h>

#include "tinyxml2.h"
#include "Engine/GameManager.h"

#include "Brick.h"



int main(int argc, char* argv[]) {
	GameManager* gm = GameManager::Get();

	gm->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);

	SDL_Color clr;
	clr.r = 0; clr.g = 255, clr.b = 255, clr.a = 255;
	std::shared_ptr<Brick> brick = std::make_shared<Brick>(50, 50, 50, 50, 0, clr);
	gm->addSceneObject(brick);

	clr.r = 255; clr.g = 0, clr.b = 255, clr.a = 255;
	std::shared_ptr<Brick> brick2 = std::make_shared<Brick>(150, 50, 50, 50, 0, clr);
	gm->addSceneObject(brick2);

	while (gm->isRunning()) {
		gm->handleEvents();
		gm->update();
		gm->render();
	}
	gm->clean();
	
	return 0;
}