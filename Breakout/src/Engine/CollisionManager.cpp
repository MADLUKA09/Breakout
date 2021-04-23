#include "CollisionManager.h"
#include "Movement.h"
#include "Body.h"
#include <algorithm>
#include <iostream>

static bool compareCollisionsByPtr(Collision* col1, Collision* col2) { 
if (*col1 < *col2) return true;
else return false; 
}

CollisionManager::CollisionManager() 
{
}

CollisionManager::~CollisionManager()
{
}

bool goingTowardsLine(const SimpleVector2<float>& linePointA, const SimpleVector2<float>& linePointB, 
					const SimpleVector2<float>& point, const SimpleVector2<float>& vel) {
	SimpleVector2<float> first = (linePointA - point).normalized();
	SimpleVector2<float> second = (linePointB - point).normalized();
	SimpleVector2<float> velNormed = vel.normalized();
	
	if (velNormed.dotProduct(first) > second.dotProduct(first)
		&& velNormed.dotProduct(second) > first.dotProduct(second))
		return true;
	else return false;
}

Collision* detectBallLineCollision(std::shared_ptr<Body> dynamicBody,
							SimpleVector2<float> linePointA, SimpleVector2<float> linePointB, float frameTime) {
	SimpleVector2<float> ballPosition = dynamicBody->getPosition();
	float ballRadius = float(dynamicBody->getShapeWidth() / 2);
	// Move ball position to center
	ballPosition.x += ballRadius;
	ballPosition.y += ballRadius;

	SimpleVector2<float> distance = Movement::distancePointLine(ballPosition, linePointA, linePointB);
	distance = distance - distance.normalized() * ballRadius; // Distance from line to edge of the ball
	distance = -distance;
	SimpleVector2<float> framePath = Movement::distanceFromVelocityAcceleration(dynamicBody->getVelocity(),	
																dynamicBody->getAcceleration(), frameTime);

	if (!goingTowardsLine(linePointA - distance.normalized() * ballRadius, linePointB - distance.normalized() * ballRadius, ballPosition, dynamicBody->getVelocity()))
		return NULL;

	SimpleVector2<float> framePathPerpendicular = framePath.projectTo(distance);

	float ratio = distance.length() / framePathPerpendicular.length();

	Collision* newCollision = new Collision{ dynamicBody, NULL, distance.normalized() * -1, NULL };
	
	std::cout << "ratio: " << ratio << std::endl;
	if (ratio > 0.f && ratio < 1.00f) {
		float timeToCollision = frameTime * ratio;
		float timeRemaining = frameTime - timeToCollision;
		FramePartition newFP = { timeToCollision, timeRemaining };

		newCollision->fp = newFP;

		return newCollision;
	}
	else return NULL;
		
}

Collision* detectDynamicStaticCollision(std::shared_ptr<Body> dynamicBody, std::shared_ptr<Body> staticBody, float frameTime)
{
	SimpleVector2<float> ballPosition = dynamicBody->getPosition();
	SimpleVector2<float> brickPosition = staticBody->getPosition();

	float ballRadius = float(dynamicBody->getShapeWidth() / 2);
	float brickWidth = float(staticBody->getShapeWidth());
	float brickHeight = float(staticBody->getShapeHeight());

	// Move position vector to the center of the ball
	ballPosition.x += float(dynamicBody->getShapeWidth()) / 2;
	ballPosition.y += float(dynamicBody->getShapeWidth()) / 2;

	std::vector<SimpleVector2<float>> brickCorners;
	brickCorners.push_back(brickPosition);
	brickCorners.push_back(brickPosition + SimpleVector2<float>(brickWidth, 0.f));
	brickCorners.push_back(brickPosition + SimpleVector2<float>(brickWidth, brickHeight));
	brickCorners.push_back(brickPosition + SimpleVector2<float>(0.f, brickHeight));

	std::vector<Collision*> theseCollisions;

	for (int i = 0; i < brickCorners.size(); ++i) {
		Collision* collision;
		if (i == brickCorners.size() - 1)
			collision = detectBallLineCollision(dynamicBody, brickCorners[i], brickCorners[0], frameTime);
		else
			collision = detectBallLineCollision(dynamicBody, brickCorners[i], brickCorners[i+1], frameTime);
		if (collision) {
			collision->body2 = staticBody;
			theseCollisions.push_back(collision);
		}
	}
	if (!theseCollisions.empty()) {
		return theseCollisions[0]; // C26816: The pointer points to memory allocated on the stack... But I don't think it does, see line 33
		std::sort(theseCollisions.begin(), theseCollisions.end(), compareCollisionsByPtr);
	}
	
	else return NULL;
}

//Collision* detectDynamicDynamicCollision(std::shared_ptr<Body> dynamicBody, std::shared_ptr<Body> staticBody, float frameTime) {
//}


void CollisionManager::detectCollisions(std::vector<std::shared_ptr<Body>>& staticBodies,
										std::vector<std::shared_ptr<Body>>& dynamicBodies, float frameTime)
{
	std::vector<std::shared_ptr<Body>> dynamicBodiesCopy = dynamicBodies;
	for (auto dBody : dynamicBodies)
		for (auto sBody : staticBodies) {
			Collision* collision = detectDynamicStaticCollision(dBody, sBody, frameTime/100);
			if (collision) {
				std::cout << "Collision" << std::endl;
				m_Collisions.push_back(collision);
			}
		}
	//for (std::vector<std::shared_ptr<Body>>::iterator it = dynamicBodies.begin(); it != dynamicBodies.end(); it++) {
	//	for (std::vector<std::shared_ptr<Body>>::iterator it = dynamicBodies.begin() + 1; it != dynamicBodies.end(); it++) {
	//}
}

