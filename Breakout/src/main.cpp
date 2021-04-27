#include <stdio.h>

#include "tinyxml2.h"
#include "Engine/Shapes.h"
#include "Engine/GameManager.h"
#include "Engine/Sprite.h"

#include "Level.h"
#include "HUD.h"

#include "Brick.h"
#include "Boundary.h"
#include "Ball.h"
#include "PlayerPad.h"


int main(int argc, char* argv[]) {
	GameManager* gm = GameManager::Get();

	// Initiate the game manager
	gm->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600/*, 60*/); // Uncomment to set framerate, default is 60

	// Shapes used
	Shapes::Circle* ballShape = new Shapes::Circle(8);
	Shapes::Rectangle* playerShape = new Shapes::Rectangle(96, 16);
	Shapes::Rectangle* boundaryShapeHor = new Shapes::Rectangle(WINDOWWIDTH, 8);
	Shapes::Rectangle* boundaryShapeVer = new Shapes::Rectangle(8, WINDOWHEIGHT);

	// Level takes care of loading the xml level file, containing brick data
	std::shared_ptr<Level> level = std::make_shared<Level>();
	gm->addSceneEntity(level);
	if (level->loadLevel("levels/Level1.xml")) {
		return 0;
	}
	// Assign level class reference to all brick objects
	Brick::setLvl(level);

	//Create boundaries and put them in the scene
	std::shared_ptr<Boundary> boundaryUp = std::make_shared<Boundary>(boundaryShapeHor, 0.f, 0.f);
	std::shared_ptr<Boundary> boundaryLeft = std::make_shared<Boundary>(boundaryShapeVer, 0.f, 0.f);
	std::shared_ptr<Boundary> boundaryRight = std::make_shared<Boundary>(boundaryShapeVer, float(WINDOWWIDTH) - 8, 0.f);
	gm->addTexture("Boundary", "assets/Textures/Boundary.bmp");
	boundaryUp->applyTexture("Boundary");
	boundaryLeft->applyTexture("Boundary");
	boundaryRight->applyTexture("Boundary");
	gm->addSceneBody(boundaryUp);
	gm->addSceneBody(boundaryLeft);
	gm->addSceneBody(boundaryRight);
	
	// Create the ball and put it in the scene
	gm->addTexture("BallLime", "assets/Textures/BallLime.bmp");
	std::shared_ptr<Ball> ball = std::make_shared<Ball>(ballShape, 316.1f, 300.f);
	gm->addSceneBody(ball);
	ball->applyTexture("BallLime");
	ball->setMaxSpeed(0.6f);

	// Create the player and put him in the scene
	gm->addTexture("PlayerTex", "assets/Textures/PPDarkCyanLime.bmp");
	std::shared_ptr<PlayerPad> player = std::make_shared<PlayerPad>(playerShape, 48.f, 568.f, ball);
	player->applyTexture("PlayerTex");
	gm->addSceneBody(player);

	// Create HUD
	gm->addTexture("LifeTex", "assets/Textures/Life.bmp");
	Sprite lifeSprite(gm->getTexture("LifeTex"), 16, 16);
	std::shared_ptr<HUD> hud = std::make_shared<HUD>(player, &lifeSprite);
	gm->addSceneEntity(hud);

	// Add references to level
	level->setPlayerAndBallRef(player, ball, hud);

	// the game loop
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