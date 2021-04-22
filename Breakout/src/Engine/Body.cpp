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

void Body::bodyMove() {
	if (!isActive())
		return;
	float FS = FRAMESCALE;
	auto v = getVelocity();
	auto a = getAcceleration();

	// Friction
	setVelocity(v.x - v.x * m_Friction * FS, v.y - v.y * m_Friction * FS);
	v = getVelocity();

	// Distance moved in this frame
	SimpleVector2<float> path = v * FS + a * FS * FS;

	setPosition(getPosition().x + path.x, getPosition().y + path.y);

	// Recalculate velocity
	setVelocity(v.x + a.x * FS, v.y + a.y * FS);
	v = getVelocity();

	if (v.length() > m_MaxSpeed) {
		auto newVel = v.normalized() * m_MaxSpeed;
		setVelocity(newVel.x, newVel.y);
	}

	else if (v.length() < 0.5f)
		setVelocity(0.f, 0.f);
}

void Body::bodyUpdate() {
	if (m_Dynamic) {
		this->m_DestRect.x = int(this->getPosition().x);
		this->m_DestRect.y = int(this->getPosition().y);
	}
}

void Body::render() {
	static SDL_Renderer* renderer = this->getGameManager()->getRenderer();
	SDL_RenderCopy(renderer, m_Texture, NULL, &m_DestRect);
}

void Body::applyTexture(const std::string& name) {
	m_Texture = this->getGameManager()->getTexture(name);
}