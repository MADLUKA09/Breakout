#include <stdio.h>

#include "tinyxml2.h"
#include "Engine/Shapes.h"
#include "Engine/GameManager.h"

#include "Level.h"

#include "Brick.h"
#include "Boundary.h"
#include "Ball.h"
#include "PlayerPad.h"


int main(int argc, char* argv[]) {
	GameManager* gm = GameManager::Get();

	gm->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600/*, 60*/);

	Shapes::Circle* ballShape = new Shapes::Circle(8);
	Shapes::Rectangle* playerShape = new Shapes::Rectangle(96, 16);
	Shapes::Rectangle* boundaryShapeHor = new Shapes::Rectangle(WINDOWWIDTH, 8);
	Shapes::Rectangle* boundaryShapeVer = new Shapes::Rectangle(8, WINDOWHEIGHT);

	std::shared_ptr<Level> level = std::make_shared<Level>();
	gm->addSceneEntity(level);
	if (level->loadLevel("levels/Level1.xml")) {
		return 0;
	}

	Brick::setLvl(level);

	std::shared_ptr<Boundary> boundaryUp = std::make_shared<Boundary>(boundaryShapeHor, 0.f, 0.f);
	std::shared_ptr<Boundary> boundaryLeft = std::make_shared<Boundary>(boundaryShapeVer, 0.f, 0.f);
	std::shared_ptr<Boundary> boundaryRight = std::make_shared<Boundary>(boundaryShapeVer, float(WINDOWWIDTH) - 5, 0.f);
	gm->addTexture("Boundary", "assets/Textures/Boundary.bmp");
	boundaryUp->applyTexture("Boundary");
	boundaryLeft->applyTexture("Boundary");
	boundaryRight->applyTexture("Boundary");
	gm->addSceneBody(boundaryUp);
	gm->addSceneBody(boundaryLeft);
	gm->addSceneBody(boundaryRight);

	gm->addTexture("BallLime", "assets/Textures/BallLime.bmp");
	std::shared_ptr<Ball> ball = std::make_shared<Ball>(ballShape, 316.1f, 300.f);
	gm->addSceneBody(ball);
	ball->applyTexture("BallLime");

	gm->addTexture("PlayerTex", "assets/Textures/PPDarkCyanLime.bmp");
	std::shared_ptr<PlayerPad> player = std::make_shared<PlayerPad>(playerShape, 48.f, 568.f, ball);
	player->applyTexture("PlayerTex");
	gm->addSceneBody(player);

	while (gm->isRunning()) {
		gm->startFrame();

		gm->handleEvents();
		gm->update();
		gm->render();

		gm->setFrameTime();

		if (level->getNrOfBricks() <= 50) {
			gm->cleanAllObjects();
			gm->addSceneEntity(level);
			if (level->loadLevel("levels/Level2.xml")) {
				return 0;
			}
			gm->addSceneBody(ball);
			gm->addSceneBody(player);
			gm->addSceneBody(boundaryUp);
			gm->addSceneBody(boundaryLeft);
			gm->addSceneBody(boundaryRight);
		}
	}
	gm->clean();
	
	return 0;
}