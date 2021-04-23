#include "Body.h"
#include "Movement.h"

Body::Body(Shapes::Shape* shape, float x, float y, bool dynamic)
	: m_Shape(shape), Entity(x, y), m_Dynamic(dynamic)
{
	if (dynamic)
		this->getGameManager()->addDynamic(std::shared_ptr<Body>(this));
	else
		this->getGameManager()->addStatic(std::shared_ptr<Body>(this));

	m_Texture = NULL;
	m_DestRect = { int(x), int(y), shape->shapeWidth(), shape->shapeHeight() };
}

Body::~Body()
{
}

void Body::bodyMove() {
	if (!isActive())
		return;
	float FS = FRAMETIME/100;
	auto v = getVelocity();
	auto a = getAcceleration();

	// New position after this frame
	SimpleVector2<float> newPos = Movement::newPositionFromVelocityAcceleration(getPosition(), v, a, FS);
	setPosition(newPos.x, newPos.y);

	// Friction
	setVelocity(v.x - v.x * m_Friction * FS, v.y - v.y * m_Friction * FS);
	v = getVelocity();

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