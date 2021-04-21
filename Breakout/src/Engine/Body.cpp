#include "Body.h"

Body::Body(Shapes::Shape* shape, int x, int y, bool dynamic)
	: m_Shape(shape), Entity(x, y), m_Dynamic(dynamic)
{
	if (dynamic)
		this->getGameManager()->addDynamic(std::shared_ptr<Body>(this));
	else
		this->getGameManager()->addStatic(std::shared_ptr<Body>(this));

	m_Texture = NULL;
	m_DestRect = { x, y, shape->shapeWidth(), shape->shapeHeight() };
}

Body::~Body()
{
}

void Body::bodyUpdate() {
	if (m_Dynamic) {
		this->m_DestRect.x = this->getPosition().x;
		this->m_DestRect.y = this->getPosition().y;
	}
}

void Body::render() {
	static SDL_Renderer* renderer = this->getGameManager()->getRenderer();
	SDL_RenderCopy(renderer, m_Texture, NULL, &m_DestRect);
}

void Body::applyTexture(const std::string& name) {
	m_Texture = this->getGameManager()->getTexture(name);
}