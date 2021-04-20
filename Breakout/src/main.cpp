#include <stdio.h>

#include "tinyxml2.h"
#include "Engine/GameManager.h"

#include "Brick.h"
#include "Ball.h"



int main(int argc, char* argv[]) {
	GameManager* gm = GameManager::Get();

	gm->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	std::shared_ptr<Brick> brick = std::make_shared<Brick>(50, 50, 64, 32, 0, "assets/textures/BrickCyan.bmp");
	gm->addSceneObject(brick);

	std::shared_ptr<Brick> brick2 = std::make_shared<Brick>(150, 50, 64, 32, 0, "assets/textures/BrickCyan.bmp");
	gm->addSceneObject(brick2);

	std::shared_ptr<Ball> ball = std::make_shared<Ball>(392, 392, 8, "assets/textures/BallLime.bmp");
	gm->addSceneObject(ball);

	while (gm->isRunning()) {
		gm->handleEvents();
		gm->update();
		gm->render();
	}
	gm->clean();
	
	return 0;
}