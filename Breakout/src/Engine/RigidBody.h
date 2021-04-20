#pragma once

#include "Entity.h"

enum class RB_Type {Rectangle, Circle, Mesh}; //Mesh unused

class RigidBody : public Entity
{
public:
	RigidBody(int x, int y, RB_Type type);
	RB_Type getRigidBodyType() { return m_Type; }

protected:
	virtual void onCollision(RigidBody* other) = 0;

private:
	RB_Type m_Type;

};

