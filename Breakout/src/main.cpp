#include <stdio.h>

#include "tinyxml2.h"
#include "Engine/Shapes.h"
#include "Engine/GameManager.h"

#include "Brick.h"
#include "Ball.h"
#include "PlayerPad.h"



int main(int argc, char* argv[]) {
	GameManager* gm = GameManager::Get();

	gm->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600/*, 60*/);

	gm->addTexture("BrickCyan", "assets/textures/BrickCyan.bmp");
	gm->addTexture("BallLime", "assets/textures/BallLime.bmp");
	gm->addTexture("PlayerTex", "assets/textures/PPDarkCyanLime.bmp");

	Shapes::Rectangle* brickShape = new Shapes::Rectangle(64, 32);
	Shapes::Circle* ballShape = new Shapes::Circle(8);
	Shapes::Rectangle* playerShape = new Shapes::Rectangle(96, 16);

	std::shared_ptr<Brick> brick = std::make_shared<Brick>(brickShape, 50, 50, 0);
	brick->applyTexture("BrickCyan");
	gm->addSceneObject(brick);
	

	std::shared_ptr<Brick> brick2 = std::make_shared<Brick>(brickShape, 150, 50, 0);
	gm->addSceneObject(brick2);
	brick2->applyTexture("BrickCyan");

	std::shared_ptr<Ball> ball = std::make_shared<Ball>(ballShape, 392, 392);
	gm->addSceneObject(ball);
	ball->applyTexture("BallLime");

	std::shared_ptr<PlayerPad> player = std::make_shared<PlayerPad>(playerShape, 368, 568);
	player->applyTexture("PlayerTex");
	gm->addSceneObject(player);

	while (gm->isRunning()) {
		gm->startFrame();

		gm->handleEvents();
		gm->update();
		gm->render();

		gm->setFrameTime();
	}
	gm->clean();
	
	return 0;
}