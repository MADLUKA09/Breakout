#pragma once

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "Engine/Entity.h"
#include "Engine/SoundEffect.h"

#include "BrickType.h"


class Level : public Entity
{
public:
	Level();
	~Level() {}

	int loadLevel(std::string levelPath);
	void entityCollision();

	int getNrOfBricks() { return m_NrOfBricks; }
	void decrementBricks() { --m_NrOfBricks; }

private:
	int m_RowCount = 0, m_ColCount = 0;
	int m_RowSpacing = 0, m_ColSpacing = 0;

	std::unordered_map<char, BrickType> m_BrickMap;

	SDL_Texture* m_BackgroundTexture = nullptr;

	void generateBricks(const char* bricks);
	int m_NrOfBricks = 0;
};
