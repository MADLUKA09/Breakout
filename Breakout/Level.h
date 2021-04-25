#pragma once

#include "SDL.h"

namespace LEVEL 
{
	enum class BrickTypes {S, M, H, I};

	struct BrickType {
		BrickTypes ID;
		SDL_Texture* m_Texture;
		int m_HitPoints;
	};

	class Level
	{
	public:
		Level();
		~Level();

	private:
		int m_CowCount, m_ColCount;
		int m_CowSpacing, m_ColSpacing;

		SDL_Texture* m_BackgroundTexture;
	};

}