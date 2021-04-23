#pragma once
#include "SimpleVector2.h"

namespace Movement {
	template <typename T>
	SimpleVector2<T> distanceFromVelocityAcceleration(SimpleVector2<T> velocity, SimpleVector2<T> acceleration, float time) {
		return velocity * time + acceleration * time * time;
	}

	template <typename T>
	SimpleVector2<T> newPositionFromVelocityAcceleration(SimpleVector2<T> position, SimpleVector2<T> velocity, SimpleVector2<T> acceleration, float time) {
		return position + distanceFromVelocityAcceleration(velocity, acceleration, time);
	}

	template <typename T>
	SimpleVector2<T> distancePointLine(SimpleVector2<T> point, SimpleVector2<T> linePointA, SimpleVector2<T> linePointB) {
		SimpleVector2<float> lineDirection = (linePointB - linePointA).normalized();
		SimpleVector2<float> d1 = linePointA - point;

		return d1 - d1.projectTo(lineDirection);
	}
}