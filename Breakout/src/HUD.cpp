#include "HUD.h"
#include <iostream>

HUD::HUD(std::shared_ptr<PlayerPad> playerRef, Sprite* life)
	:m_playerRef(playerRef), m_Life(life)
{
	m_ShowStartingScreen = true;
	m_GameOver = false;
	m_GameWin = false;
	m_Lives = 0;

	if (TTF_Init() == -1)
		std::cout << "Error initing ttf!" << std::endl;
	TTF_Font* something = m_PointsFont = TTF_OpenFont("assets/fonts/OpenSansRegular.ttf", 32);
	if (!m_PointsFont)
		std::cout << "Error loading font file" << std::endl;

	m_PointsColor = { 0, 255, 155 }; // I like lime
	SDL_Surface* temp = TTF_RenderText_Solid(m_PointsFont, std::to_string(m_playerRef->getPoints()).c_str(), m_PointsColor);
	pointsTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	SDL_FreeSurface(temp);
	m_Points = new Sprite(pointsTexture, temp->w, temp->h);

	temp = TTF_RenderText_Solid(m_PointsFont, "Current Level: 0", m_PointsColor);
	levelTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	SDL_FreeSurface(temp);
	m_LevelSpr = new Sprite(pointsTexture, temp->w, temp->h);
}

void HUD::updateScore()
{
	SDL_Surface* temp = TTF_RenderText_Solid(m_PointsFont, std::to_string(m_playerRef->getPoints()).c_str(), m_PointsColor);
	SDL_DestroyTexture(pointsTexture);
	pointsTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	delete(m_Points);
	m_Points = new Sprite(pointsTexture, temp->w, temp->h);
	SDL_FreeSurface(temp);
}

void HUD::updateLevel(int level) {
	static std::string currentLevel = "Current Level: ";
	SDL_Surface* temp = TTF_RenderText_Solid(m_PointsFont, (currentLevel + std::to_string(level)).c_str(), m_PointsColor);
	SDL_DestroyTexture(levelTexture);
	levelTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	delete(m_LevelSpr);
	m_LevelSpr = new Sprite(levelTexture, temp->w, temp->h);
	SDL_FreeSurface(temp);
}

void HUD::render() {
	static SDL_Renderer* renderer = gm->getRenderer();
	static int lvlx = WINDOWWIDTH / 2 - m_LevelSpr->getWidth() / 2;
	static int lvly = 10;
	for (int i = 0; i < m_Lives; ++i)
		m_Life->draw(renderer, 10 + i * m_Life->getWidth(), 10);

	m_Points->draw(renderer, 16, 16);
	m_LevelSpr->draw(renderer, lvlx, lvly);

	if (m_ShowStartingScreen) {
		showStartScreen();
	}
	else if (m_GameOver) {
		showEndScreen();
	}
	else if (m_GameWin)
		showWinScreen();
}

void HUD::onKeyboardDown(const SDL_Keycode& keyCode)
{
	if (keyCode == SDLK_SPACE)
		m_ShowStartingScreen = false;
}

void HUD::showStartScreen()
{
	static SDL_Renderer* renderer= gm->getRenderer();
	static TTF_Font* startFont = TTF_OpenFont("assets/fonts/OpenSansBold.ttf", 64);
	static std::string startText = "Press space to start";
	static SDL_Surface* temp = TTF_RenderText_Solid(startFont, startText.c_str(), m_PointsColor);
	static SDL_Texture* startTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	static Sprite startSprite(startTexture, temp->w, temp->h);
	static int x = WINDOWWIDTH / 2 - temp->w / 2;
	static int y = WINDOWHEIGHT / 2;
	static bool freed = false;
	if (!freed) {
		SDL_FreeSurface(temp);
		freed = true;
	}

	startSprite.draw(renderer, x, y);
}

void HUD::showEndScreen() {
	static SDL_Renderer* renderer = gm->getRenderer();
	static TTF_Font* endFont = TTF_OpenFont("assets/fonts/OpenSansBold.ttf", 64);
	static std::string endText = "GAME OVER!";
	static SDL_Surface* temp = TTF_RenderText_Solid(endFont, endText.c_str(), m_PointsColor);
	static SDL_Texture* endTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	static Sprite endSprite(endTexture, temp->w, temp->h);
	static int x = WINDOWWIDTH / 2 - temp->w / 2;
	static int y = WINDOWHEIGHT / 2;

	static bool freed = false;
	if (!freed) {
		SDL_FreeSurface(temp);
		freed = true;
	}

	endSprite.draw(renderer, x, y);
	showEndPoints();
}

void HUD::showWinScreen() {
	static SDL_Renderer* renderer = gm->getRenderer();
	static TTF_Font* endFont = TTF_OpenFont("assets/fonts/OpenSansBold.ttf", 64);
	static std::string endText = "YOU WIN!";
	static SDL_Surface* temp = TTF_RenderText_Solid(endFont, endText.c_str(), m_PointsColor);
	static SDL_Texture* endTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp);
	static Sprite endSprite(endTexture, temp->w, temp->h);
	static int x = WINDOWWIDTH / 2 - temp->w / 2;
	static int y = WINDOWHEIGHT / 2;

	static bool freed = false;
	if (!freed) {
		SDL_FreeSurface(temp);
		freed = true;
	}

	endSprite.draw(renderer, x, y);
	showEndPoints();
}

void HUD::showEndPoints() {
	static SDL_Renderer* renderer = gm->getRenderer();
	static std::string endScore = "SCORE: " + std::to_string(m_playerRef->getPoints());
	static SDL_Surface* temp2 = TTF_RenderText_Solid(m_PointsFont, endScore.c_str(), m_PointsColor);
	static SDL_Texture* endPointTexture = SDL_CreateTextureFromSurface(gm->getRenderer(), temp2);
	static Sprite endPoints(endPointTexture, temp2->w, temp2->h);
	static int x2 = WINDOWWIDTH / 2 - temp2->w / 2;
	static int y2 = 398;

	static bool freed = false;
	if (!freed) {
		SDL_FreeSurface(temp2);
		freed = true;
	}

	endPoints.draw(renderer, x2, y2);
}