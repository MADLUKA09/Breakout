#pragma once
#include "SDL.h"
#include "Shapes.h"
#include "Entity.h"
#include <string>

class Body : public Entity
{
public:
	Body(Shapes::Shape*, float x, float y, bool dynamic);
	~Body();

	bool isDynamic() { return m_Dynamic; }

	// Shape
	int getShapeWidth() { return m_Shape->shapeWidth(); }
	int getShapeHeight() { return m_Shape->shapeHeight(); }

	// Texturing
	SDL_Texture* getTexture() { return m_Texture; }
	SDL_Rect& getDestRect() { return m_DestRect; }
	void applyTexture(const std::string& name);

	// Movement
	void setVelocity(float x, float y) { m_Velocity.x = x; m_Velocity.y = y; }
	void setAcceleration(float x, float y) { m_Acceleration.x = x; m_Acceleration.y = y; }
	SimpleVector2<float> getVelocity() { return m_Velocity; }
	SimpleVector2<float> getAcceleration() { return m_Acceleration; }
	void setFriction(float fr) { m_Friction = fr; }
	void setMaxSpeed(float sp) { m_MaxSpeed = sp; }
	
	void bodyMove();
	void bodyUpdate();

protected:
	virtual void update() {}
	virtual void render();

private:
	Shapes::Shape*	m_Shape;
	bool			m_Dynamic;

	// Movement
	SimpleVector2<float> m_Velocity;
	SimpleVector2<float> m_Acceleration;
	float m_Friction = 0.1f;
	float m_MaxSpeed = 100.f;

	// Texturing
	SDL_Texture* m_Texture;
	SDL_Rect	 m_DestRect;
};