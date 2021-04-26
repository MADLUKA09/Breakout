#pragma once

#include "SDL.h"
#include "Engine/Entity.h"
#include "Engine/SoundEffect.h"
#include "Brick.h"
#include <unordered_map>
#include <string>

namespace LEVEL
{
	enum class BrickTypes {S, M, H, I};

	struct BrickType {
		char typeID;
		bool breakable;
		
		std::string texture;

		int hitPoints;
		int breakScore;

		SoundEffect hitSound;
		SoundEffect breakSound;
	};

	class Level : public Entity
	{
	public:
		Level();
		~Level();

		int loadLevel(std::string levelPath);

	private:
		int m_RowCount = 0, m_ColCount = 0;
		int m_RowSpacing = 0, m_ColSpacing = 0;

		std::unordered_map<char, BrickType> m_BrickMap;

		SDL_Texture* m_BackgroundTexture = nullptr;

		void generateBricks(const char* bricks);
	};

}