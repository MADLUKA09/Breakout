#include "CollisionManager.h"
#include "Movement.h"
#include "Body.h"
#include <algorithm>
#include <iostream>
#include <math.h>

static bool compareCollisionsByPtr(Collision* col1, Collision* col2) { 
if (*col1 > *col2) return true;
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

Collision* detectBallPointCollision(const std::shared_ptr<Body>& ball, const SimpleVector2<float>& pointVel,
									const SimpleVector2<float>& pointAcc, const SimpleVector2<float>& point, const float& frameTime) {

	float remainingTime = frameTime - ball->getCurrentTime();
	const SimpleVector2<float> startingBallPosition = ball->getPosition() 
													+ SimpleVector2<float>(float(ball->getShapeWidth())/2, float(ball->getShapeHeight())/2);
	const SimpleVector2<float> endingBallPosition = 
		Movement::newPositionFromVelocityAcceleration(startingBallPosition, ball->getVelocity() - pointVel,
														ball->getAcceleration() - pointAcc, remainingTime);

	const float ballRadius = float(ball->getShapeWidth()) / 2;
	const float x = Movement::distancePointLine(point, startingBallPosition, endingBallPosition).length();

	if (x > ballRadius) // If ball is not moving towards the point
		return nullptr;

	const SimpleVector2<float> path = endingBallPosition - startingBallPosition;
	const SimpleVector2<float> distanceProj = (point - startingBallPosition).projectTo(path);

	const float offset = std::sqrt(ballRadius * ballRadius - x * x);

	const SimpleVector2<float> pathToCol = distanceProj - distanceProj.normalized() * offset;

	const float ratio = pathToCol.dotProduct(path.normalized()) / path.length();
	std::cout << "ratio: " << ratio << std::endl;
	if (ratio > 0.f && ratio < 1.f) {
		const SimpleVector2<float> colNormal = ((startingBallPosition + pathToCol) - point).normalized();
		Collision* newCollision = new Collision{ ball, NULL, colNormal, NULL };
		float timeToCollision = frameTime * ratio;
		float timeRemaining = frameTime - timeToCollision;
		FramePartition newFP = { timeToCollision, timeRemaining };

		newCollision->fp = newFP;

		return newCollision;
	}

	return nullptr;
}

Collision* detectBallLineCollision(const std::shared_ptr<Body>& dynamicBody, const SimpleVector2<float>& otherBodyVelocity, SimpleVector2<float> otherBodyAcceleration,
							const SimpleVector2<float>& linePointA, const SimpleVector2<float>& linePointB, const float& frameTime) {
	SimpleVector2<float> ballPosition = dynamicBody->getPosition();
	float ballRadius = float(dynamicBody->getShapeWidth() / 2);
	// Move ball position to center
	ballPosition.x += ballRadius;
	ballPosition.y += ballRadius;

	float remainingTime = frameTime - dynamicBody->getCurrentTime();

	const SimpleVector2<float> distance = Movement::distancePointLine(ballPosition, linePointA, linePointB);
	const SimpleVector2<float> distanceToEdge = distance - distance.normalized() * ballRadius; // Distance from line to edge of the ball
	
	const SimpleVector2<float> framePath = Movement::distanceFromVelocityAcceleration(dynamicBody->getVelocity(),	
																dynamicBody->getAcceleration(), remainingTime);

	const SimpleVector2<float> framePathRelative = framePath - Movement::distanceFromVelocityAcceleration(otherBodyVelocity,
																						otherBodyAcceleration, remainingTime);


	if (!goingTowardsLine(linePointA - distance.normalized() * ballRadius, linePointB - distance.normalized() * ballRadius, ballPosition, framePathRelative))
		return nullptr;

	float pathDotDistance = framePath.dotProduct(distanceToEdge.normalized());

	float ratio = distanceToEdge.length() / pathDotDistance;
	
	//std::cout << "ratio: " << ratio << std::endl;
	if (ratio > 0.f && ratio < 1.00f) {
		Collision* newCollision = new Collision{ dynamicBody, NULL, distanceToEdge.normalized(), NULL };
		float timeToCollision = frameTime * ratio;
		float timeRemaining = frameTime - timeToCollision;
		FramePartition newFP = { timeToCollision, timeRemaining };

		newCollision->fp = newFP;

		return newCollision;
	}
	else return nullptr;
		
}

// Ball to bricks collisions
Collision* detectBallBrickCollision(const std::shared_ptr<Body>& ball, const std::shared_ptr<Body>& brick, const float& frameTime)
{
	// Move the bodies to the same point in frame time
	float time = std::max(ball->getCurrentTime(), brick->getCurrentTime());
	ball->bodyMove(time - ball->getCurrentTime());
	brick->bodyMove(time - brick->getCurrentTime());

	SimpleVector2<float> ballPosition = ball->getPosition();
	SimpleVector2<float> brickPosition = brick->getPosition();

	float ballRadius = float(ball->getShapeWidth() / 2);
	float brickWidth = float(brick->getShapeWidth());
	float brickHeight = float(brick->getShapeHeight());

	// Move position vector to the center of the ball
	ballPosition.x += float(ball->getShapeWidth()) / 2;
	ballPosition.y += float(ball->getShapeWidth()) / 2;

	std::vector<SimpleVector2<float>> brickCorners;
	brickCorners.push_back(brickPosition);
	brickCorners.push_back(brickPosition + SimpleVector2<float>(brickWidth, 0.f));
	brickCorners.push_back(brickPosition + SimpleVector2<float>(brickWidth, brickHeight));
	brickCorners.push_back(brickPosition + SimpleVector2<float>(0.f, brickHeight));

	std::vector<Collision*> theseCollisions;

	for (std::vector<SimpleVector2<float>>::iterator it = brickCorners.begin(); it != brickCorners.end(); ++it) {
		Collision* collision;
		if (it == brickCorners.end() - 1)
			collision = detectBallLineCollision(ball, brick->getVelocity(), brick->getAcceleration(), *it, *brickCorners.begin(), frameTime);
		else
			collision = detectBallLineCollision(ball, brick->getVelocity(), brick->getAcceleration(), *it, *(it + 1), frameTime);
		if (collision) {
			collision->body2 = brick;
			theseCollisions.push_back(collision);
		}
	}

	if (theseCollisions.empty()) {
		Collision* collision;
		for (auto& point : brickCorners) {
			collision = detectBallPointCollision(ball, brick->getVelocity(), brick->getAcceleration(), point, frameTime);
			if (collision) {
				collision->body2 = brick;
				theseCollisions.push_back(collision);
			}
		}
	}

	if (!theseCollisions.empty()) {
		return theseCollisions[0]; // C26816: The pointer points to memory allocated on the stack... But I don't think it does, see line 33
		std::sort(theseCollisions.begin(), theseCollisions.end(), compareCollisionsByPtr);
	}
	
	else return nullptr;
}

void detectInitialCollisions(CollisionQueue& collisionQRef, const BodiesVector& staticBodies,
							const BodiesVector& dynamicBodies, const float& frameTime) {
	for (BodiesVector::const_iterator itD = dynamicBodies.begin(); itD != dynamicBodies.end(); ++itD) {
		if ((*itD)->getVelocity().length() < (*itD)->getMinSpeed() ||!(*itD)->isActive())
			continue;
		Collision* collision = nullptr;
		for (BodiesVector::const_iterator itS = staticBodies.begin(); itS != staticBodies.end(); ++itS) {
			if (!(*itS)->isActive())
				continue;
			Collision* newCollision = detectBallBrickCollision(*itD, *itS, frameTime);
			if (newCollision)
				if (collision == nullptr || newCollision->fp.timePassed < collision->fp.timePassed) {
					std::cout << "Collision" << std::endl;
					collision = newCollision;
				}
		}

		for (BodiesVector::const_iterator itS = itD + 1; itS != dynamicBodies.end(); ++itS) {
			Collision* newCollision = detectBallBrickCollision(*itD, *itS, frameTime);
			if (newCollision)
				if (collision == nullptr || newCollision->fp.timePassed < collision->fp.timePassed) {
					std::cout << "Collision" << std::endl;
					collision = newCollision;
				}
		}
		if (collision) {
			std::cout << "Collision" << std::endl;
			collisionQRef.emplace(*collision);
		}
	}
}

void checkAfterCollisions(CollisionQueue& collisionQRef, const std::shared_ptr<Body>& body1,
						const std::shared_ptr<Body>& body2, const BodiesVector& staticBodies,
						const BodiesVector& dynamicBodies, const float& frameTime) {
	Collision* collision = nullptr;

	for (BodiesVector::const_iterator itS = staticBodies.begin(); itS != staticBodies.end(); ++itS) {
		if (!(*itS)->isActive() || *itS == body2)
			continue;
		Collision* newCollision = detectBallBrickCollision(body1, *itS, frameTime);
		if (newCollision)
			if (collision == nullptr || newCollision->fp.timePassed < collision->fp.timePassed) {
				std::cout << "Collision" << std::endl;
				collision = newCollision;
			}
	}

	for (BodiesVector::const_iterator itD = dynamicBodies.begin() + 1; itD != dynamicBodies.end(); ++itD) {
		if (*itD == body1 || *itD == body2 || !(*itD)->isActive())
			continue;
		Collision* newCollision = detectBallBrickCollision(body1, *itD, frameTime);
		if (newCollision)
			if (collision == nullptr || newCollision->fp.timePassed < collision->fp.timePassed) {
				std::cout << "Collision" << std::endl;
				collision = newCollision;
			}
	}

	if (collision) {
		std::cout << "Collision" << std::endl;
		collisionQRef.emplace(*collision);
		collision = nullptr;
	}

	if (body2->isDynamic() && body2->isActive()) {
		for (BodiesVector::const_iterator itS = staticBodies.begin(); itS != staticBodies.end(); ++itS) {
			if (!(*itS)->isActive() || *itS == body1)
				continue;
			Collision* collision = detectBallBrickCollision(body2, *itS, frameTime);
			if (collision) {
				std::cout << "Collision" << std::endl;
				collisionQRef.emplace(*collision);
			}
		}

		for (BodiesVector::const_iterator itD = dynamicBodies.begin() + 1; itD != dynamicBodies.end(); ++itD) {
			if (*itD == body1 || *itD == body2)
				continue;
			Collision* collision = detectBallBrickCollision(body2, *itD, frameTime);
			if (collision) {
				std::cout << "Collision" << std::endl;
				collisionQRef.emplace(*collision);
			}
		}
	}
}

Collision CollisionManager::solveFirstCollision() {
	Collision collision = m_CollisionsQ.top(); // Take first collision
	m_CollisionsQ.pop();					   // Pop it

	auto& body1 = collision.body1;
	auto& body2 = collision.body2;
	// Move bodies to the collision time
	body1->bodyMove(collision.fp.timePassed - body1->getCurrentTime());
	body2->bodyMove(collision.fp.timePassed - body2->getCurrentTime());

	// Mirror the velocity around the collision vector
	auto& b1Vel = collision.body1->getVelocity();
	collision.body1->setVelocity(b1Vel - b1Vel.projectTo(collision.collisionVector) * 2);
	body1->onCollision(body2);
	body2->onCollision(body1);

	return collision;
}

void CollisionManager::detectCollisions(BodiesVector& staticBodies,
										BodiesVector& dynamicBodies, const float& frameTime)
{	
	detectInitialCollisions(m_CollisionsQ, staticBodies, dynamicBodies, frameTime);
	

	while (!m_CollisionsQ.empty()) {
		Collision collisionSolved = solveFirstCollision();
		auto& body1 = collisionSolved.body1;
		auto& body2 = collisionSolved.body2;
		auto& timeRemaining = collisionSolved.fp.timeRemaining;

		checkAfterCollisions(m_CollisionsQ, body1, body2, staticBodies, dynamicBodies, frameTime);
	}

	for (BodiesVector::iterator itD = dynamicBodies.begin(); itD != dynamicBodies.end(); ++itD) {
		(*itD)->bodyMove(frameTime - (*itD)->getCurrentTime());
	}
}

void CollisionManager::moveWithCollisions(BodiesVector& staticBodies,
	BodiesVector& dynamicBodies, float frameTime)
{
	detectCollisions(staticBodies, dynamicBodies, frameTime);

}