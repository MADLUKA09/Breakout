#pragma once
#include <vector>
#include "SDL_ttf.h"
#include "Engine/Entity.h"
#include "Engine/Sprite.h"
#include "PlayerPad.h"

class HUD : public Entity
{
public:
	HUD(std::shared_ptr<PlayerPad> playerRef, Sprite* life);
	void updateScore();
	void render();
	void onKeyboardDown(const SDL_Keycode& keyCode);
	void updateLives(int lives) { m_Lives = lives; }
	void updateLevel(int level);
	void setGameOver() { m_GameOver = true; }
	void setGameWin() { m_GameWin = true; }

	void showStartScreen();
	void showEndScreen();
	void showWinScreen();
	void showEndPoints();

private:
	Sprite* m_Life;
	Sprite* m_Points;
	Sprite* m_LevelSpr;
	SDL_Texture* pointsTexture;
	SDL_Texture* levelTexture;
	int m_Lives;

	TTF_Font* m_PointsFont;
	SDL_Color m_PointsColor;
	std::shared_ptr<PlayerPad> m_playerRef;

	bool m_ShowStartingScreen;
	bool m_GameOver;
	bool m_GameWin;
};

