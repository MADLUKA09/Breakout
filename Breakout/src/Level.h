#pragma once

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "Engine/Entity.h"
#include "Engine/SoundEffect.h"

#include "BrickType.h"
#include "PlayerPad.h"
#include "Ball.h"
#include "HUD.h"


class Level : public Entity
{
public:
	Level();
	~Level() {}

	void update();
	void render();
	void onKeyboardDown(const SDL_Keycode& keyCode);

	int loadLevel(std::string levelPath);
	int getNrOfBricks() { return m_NrOfBricks; }
	void decrementBricks();

	void awardPoints(int points) { m_PlayerRef->addPoints(points); }

	void setPlayerAndBallRef(std::shared_ptr<PlayerPad> pl, std::shared_ptr<Ball> ball, std::shared_ptr<HUD> hud);

private:
	int m_RowCount, m_ColCount;
	int m_RowSpacing, m_ColSpacing;

	std::unordered_map<char, BrickType> m_BrickMap;

	SDL_Texture* m_BackgroundTexture;

	void generateBricks(const char* bricks);
	void levelUp();

	int m_NrOfBricks;
	int m_Level;
	int m_Lives;

	std::shared_ptr<PlayerPad>	m_PlayerRef;
	std::shared_ptr<Ball>		m_BallRef;
	std::shared_ptr<HUD>		m_HUD;
};
