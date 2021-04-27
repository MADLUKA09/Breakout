#include "Level.h"
#include "tinyxml2.h"
#include <sstream>

#include "Engine/Shapes.h"
#include "Brick.h"

Level::Level()
{
	m_NrOfBricks = 0;
	m_Level = 1;
	m_Lives = 3;
	m_RowCount = 0;
	m_ColCount = 0;
	m_RowSpacing = 0;
	m_ColSpacing = 0;
	m_BackgroundTexture = nullptr;
}

int Level::loadLevel(std::string levelPath)
{
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(levelPath.c_str());

	tinyxml2::XMLElement* XLevel = xmlDoc.FirstChildElement("Level");

	m_RowCount = XLevel->FindAttribute("RowCount")->IntValue();
	m_ColCount = XLevel->FindAttribute("ColumnCount")->IntValue();
	m_RowSpacing = XLevel->FindAttribute("RowSpacing")->IntValue();
	m_ColSpacing = XLevel->FindAttribute("ColumnSpacing")->IntValue();
	const char* texPath = XLevel->FindAttribute("BackgroundTexture")->Value();

	gm->addTexture("Background", texPath);
	m_BackgroundTexture = gm->getTexture("Background");

	tinyxml2::XMLElement* XBrickTypes = XLevel->FirstChildElement("BrickTypes");
	tinyxml2::XMLElement* XBrickType = XBrickTypes->FirstChildElement("BrickType");



	const char brickID = XBrickType->FindAttribute("Id")->Value()[0];
	m_BrickMap.emplace(std::make_pair(brickID, BrickType()));

	auto& brickType = m_BrickMap[brickID];
	brickType.typeID = brickID;
	brickType.hitPoints = XBrickType->FindAttribute("HitPoints")->IntValue();
	brickType.hitSound.loadSound(XBrickType->FindAttribute("HitSound")->Value());

	texPath = XBrickType->FindAttribute("Texture")->Value();
	gm->addTexture(&brickID, texPath);
	brickType.texture = &brickID;

	const tinyxml2::XMLAttribute* soundPathAtt = XBrickType->FindAttribute("BreakSound");
	const tinyxml2::XMLAttribute* breakScoreAtt = XBrickType->FindAttribute("BreakScore");

	if (soundPathAtt) {
		brickType.breakSound.loadSound(soundPathAtt->Value());
		brickType.breakable = true;
		brickType.breakScore = breakScoreAtt->IntValue();
	}
	else brickType.breakable = false;

	while (XBrickType = XBrickType->NextSiblingElement()) {
		const char brickID = XBrickType->FindAttribute("Id")->Value()[0];
		m_BrickMap.emplace(std::make_pair(brickID, BrickType()));

		auto& brickType = m_BrickMap[brickID];
		brickType.typeID = brickID;
		brickType.hitPoints = XBrickType->FindAttribute("HitPoints")->IntValue();
		brickType.hitSound.loadSound(XBrickType->FindAttribute("HitSound")->Value());

		texPath = XBrickType->FindAttribute("Texture")->Value();
		gm->addTexture(&brickID, texPath);
		brickType.texture = &brickID;

		const tinyxml2::XMLAttribute* soundPathAtt = XBrickType->FindAttribute("BreakSound");
		const tinyxml2::XMLAttribute* breakScoreAtt = XBrickType->FindAttribute("BreakScore");

		if (soundPathAtt) {
			brickType.breakSound.loadSound(soundPathAtt->Value());
			brickType.breakable = true;
			brickType.breakScore = breakScoreAtt->IntValue();
		}
		else brickType.breakable = false;
	}

	tinyxml2::XMLElement* XBricks = XLevel->FirstChildElement("Bricks");
	auto bricks = XBricks->FirstChild()->Value();

	generateBricks(bricks);

	return xmlDoc.ErrorID();
}

void Level::generateBricks(const char* bricks) {
	std::stringstream ss;
	ss.str(bricks);

	float brickX = 20.f;
	float brickY = 20.f;
	int brickLength = (WINDOWWIDTH - 40 - m_ColSpacing * m_ColCount) / m_ColCount;
	int brickHeight = (WINDOWHEIGHT - 200 - m_ColSpacing * m_RowCount) / m_ColCount;

	Shapes::Rectangle* brickShape = new Shapes::Rectangle(brickLength, brickHeight);

	int colNumber = 1;
	int rowNumber = 0;

	while (ss) {
		char brickType;
		brickType = ss.get();

		std::shared_ptr<Brick> brick;

		switch (brickType) {
		case '\n':
			if (rowNumber > 0)
				brickY += brickHeight + m_RowSpacing;
			++rowNumber;
			colNumber = 1;
			brickX = 20.f;
			break;
		case ' ':
			++colNumber;
			brickX += brickLength + m_ColSpacing;
			break;
		case 'H':
			brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['H']);
			gm->addSceneBody(brick);
			++m_NrOfBricks;
			break;
		case 'M':
			brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['M']);
			gm->addSceneBody(brick);
			++m_NrOfBricks;
			break;
		case 'S':
			brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['S']);
			gm->addSceneBody(brick);
			++m_NrOfBricks;
			break;
		case 'I':
			brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['I']);
			gm->addSceneBody(brick);
			break;
		}
	}
}

void Level::decrementBricks()
{
	--m_NrOfBricks;
	m_HUD->updateScore();
	if (m_NrOfBricks == 0)
		levelUp();
}

void Level::levelUp() {
	
	++m_Level;
	m_HUD->updateLevel(m_Level);
	if (m_Level > 3) {
		m_HUD->setGameWin();
		m_BallRef->setActive(false);
		return;
	}
	gm->removeBodiesByLayer(1);   // Remove Bricks
	m_BallRef->setMaxSpeed(m_BallRef->getMaxSpeed() + 0.3f);
	m_BallRef->entityInit();
	loadLevel("levels/Level" + std::to_string(m_Level) + ".xml");
}

void Level::setPlayerAndBallRef(std::shared_ptr<PlayerPad> pl, std::shared_ptr<Ball> ball, std::shared_ptr<HUD> hud) {
	m_PlayerRef = pl;
	m_BallRef = ball;
	m_HUD = hud;
	m_HUD->updateLives(m_Lives);
	m_HUD->updateLevel(m_Level);
}

void Level::render() {
	static SDL_Renderer* renderer =  gm->getRenderer();
	SDL_RenderCopy(renderer, m_BackgroundTexture, NULL, NULL);
}

void Level::update() {
	if (m_BallRef->getPosition().y > m_PlayerRef->getPosition().y) {
		--m_Lives;
		m_HUD->updateLives(m_Lives);
		gm->removeInactiveObjects();
		if (m_Lives <= 0) {
			m_BallRef->setActive(false);
			m_HUD->setGameOver();
		}
		m_BallRef->entityInit();
	}
}

void Level::onKeyboardDown(const SDL_Keycode& keyCode){
	switch (keyCode) {
	case SDLK_r:						// Reset the ball, in case of bugs
		m_BallRef->entityInit();
		break;
	case SDLK_l:
		++m_Lives;						// Cheater mode
		m_PlayerRef->addPoints(-1000);
		m_HUD->updateLives(m_Lives);
		m_HUD->updateScore();
		break;
	case SDLK_u:
		levelUp();
		break;
	}
}