#pragma once

#include <memory>
#include <unordered_set>
#include "SimpleVector2.h"

class Body;
class IDType;

struct FramePartition {
	float timePassed;
	float timeRemaining;
};


struct Collision {
	std::shared_ptr<Body> body1;
	std::shared_ptr<Body> body2;

	SimpleVector2<float> collisionVector;

	FramePartition fp;

	bool operator>(const Collision& other) const {
		if (this->fp.timePassed > other.fp.timePassed)
			return true;
		else return false;
	}

	bool operator<(const Collision& other) const {
		if (this->fp.timePassed > other.fp.timePassed)
			return false;
		else return true;
	}
};

struct CollisionQueue {
private:
	Collision* colArr = (Collision*)malloc(sizeof(Collision) * 30);
	std::unordered_set<IDType> bodiesContained;

public:
	int size = 0;

	void insert(Collision collision) {
		++size;
		Collision* temp = colArr;
		int counter = 1;
		if (size == 1) {
			*colArr = collision;
			return;
		}
		while (collision < *temp && temp < colArr + size) {
			temp++;
			counter++;
		}
		if(bodiesContained.count(collision.body1->getID()))

		memcpy(temp + 1, temp, size - counter);
	}

	void remove(int index) {
		if (index < size)
			memcpy(colArr + index, colArr + index + 1, size - index);
		--size;
	}

	int findIndex(std::shared_ptr<Body> body) {
		Collision* temp = colArr;
		int counter = 0;
		while (temp < colArr + size) {
			if ((*temp).body1 == body)
				return counter;
			if ((*temp).body2 == body)
				return counter;
			++counter;
			++temp;
		}
		return -1;
	}

	Collision pop() {
		try {
			if (size <= 0) {
				throw(size);
			}
			--size;
			return *(colArr + size);
		}
		catch (int sizeNum) {
			printf("Trying to pop from an empty queue\n");
			return *colArr;
		}
	}

	bool empty() {
		if (size == 0)
			return true;
		else return false;
	}
};

using BodiesVector = std::vector<std::shared_ptr<Body>>;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void moveWithCollisions(BodiesVector& dynamicBodies, BodiesVector& staticBodies,float frameTime);

private:
	CollisionQueue m_CollisionsQ;

	Collision solveFirstCollision();
};

