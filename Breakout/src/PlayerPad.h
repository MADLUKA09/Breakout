#pragma once
#include <string>

#include "Engine/Body.h"

class PlayerPad : public Body
{
public:
	PlayerPad(Shapes::Shape* shape, int x, int y);
	~PlayerPad();

protected:
	// From Entity
	virtual void init();
	virtual void handleEvents();
	virtual void update();
};

