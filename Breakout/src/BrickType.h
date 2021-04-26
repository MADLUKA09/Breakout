#pragma once

struct BrickType {
	char typeID;
	bool breakable;

	std::string texture;

	int hitPoints;
	int breakScore;

	SoundEffect hitSound;
	SoundEffect breakSound;
};