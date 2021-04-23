#pragma once

#include <memory>
#include <vector>
#include "SimpleVector2.h"


struct FramePartition {
	float timePassed;
	float timeRemaining;
};

class Body;

struct Collision {
	std::shared_ptr<Body> body1;
	std::shared_ptr<Body> body2;

	SimpleVector2<float> collisionVector;

	FramePartition fp;

	bool operator>(const Collision& other) {
		if (this->fp.timePassed > other.fp.timePassed)
			return true;
		else return false;
	}

	bool operator<(const Collision& other) {
		if (this->fp.timePassed > other.fp.timePassed)
			return false;
		else return true;
	}
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void detectCollisions(std::vector<std::shared_ptr<Body>>& staticBodies,
		std::vector<std::shared_ptr<Body>>& dynamicBodies, float frameTime);

private:
	std::vector<Collision*> m_Collisions;
};

