#pragma once
#include "SDL.h"
#include "Shapes.h"
#include "Entity.h"
#include <string>

class Body : public Entity
{
public:
	Body(Shapes::Shape*, int x, int y, bool dynamic);
	~Body();

	bool isDynamic() { return m_Dynamic; }

	SDL_Texture* getTexture() { return m_Texture; }
	SDL_Rect& getDestRect() { return m_DestRect; }
	void applyTexture(const std::string& name);
	
	void bodyUpdate();

protected:
	virtual void update() {}
	virtual void render();

private:
	Shapes::Shape*	m_Shape;
	bool			m_Dynamic;

	// Texturing
	SDL_Texture* m_Texture;
	SDL_Rect	 m_DestRect;
};