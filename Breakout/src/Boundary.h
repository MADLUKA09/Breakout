#include "Engine/Body.h"
#include "Engine/Shapes.h"

class Boundary : public Body {
public:
	Boundary(Shapes::Shape* shape, float x, float y, std::shared_ptr<Entity> parent = nullptr)
		: Body(shape, x, y, false, parent) {}

};