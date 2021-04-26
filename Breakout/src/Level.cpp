#include "Level.h"
#include "tinyxml2.h"
#include <sstream>

namespace LEVEL {

	Level::Level()
	{
	}

	Level::~Level()
	{
	}

	int Level::loadLevel(std::string levelPath)
	{
		tinyxml2::XMLDocument xmlDoc;
		xmlDoc.LoadFile(levelPath.c_str());

		tinyxml2::XMLElement* XLevel = xmlDoc.FirstChildElement("Level");

		this->m_RowCount = XLevel->FindAttribute("RowCount")->IntValue();
		this->m_ColCount = XLevel->FindAttribute("ColumnCount")->IntValue();
		this->m_RowSpacing = XLevel->FindAttribute("RowSpacing")->IntValue();
		this->m_ColSpacing = XLevel->FindAttribute("ColumnSpacing")->IntValue();
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
		int brickLength = (WINDOWWIDTH - 40 - m_ColSpacing) / m_ColCount;
		int brickHeight = (WINDOWHEIGHT - 200 - m_ColSpacing) / m_ColCount;

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
					brickY += brickHeight;
				++rowNumber;
				colNumber = 1;
				break;
			case ' ':
				++colNumber;
				brickX += brickLength;
				break;
			case 'H':
				brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['H']);
				addSubObject(brick);
				break;
			case 'M':
				brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['M']);
				addSubObject(brick);
				break;
			case 'S':
				brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['S']);
				addSubObject(brick);
				break;
			case 'I':
				brick = std::make_shared<Brick>(brickShape, brickX, brickY, m_BrickMap['I']);
				addSubObject(brick);
				break;
			}
		}
	}
}