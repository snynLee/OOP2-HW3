#include "Wall.h"

Wall::Wall(GameObject* parent, const Position& pos, const Dimension& dim)
	: GameObject(parent, "", pos, dim), valid(true)
{}


void Wall::draw()
{
	char* shape = const_cast<char *>(renderer->getShape());
	auto dim = transform->getDimension();
	size_t sz = (size_t)dim.x * dim.y;
	memset(shape, valid == true ? '@' : 'X', sz);
	shape[sz] = '\0';

	//GameObject::draw();
	renderer->update();
}

bool Wall::isOverlapping(const Position& from, const Position& to) const
{
	if (!transform) return false;

	return transform->isOverlapping(from, to);
}

// void Wall::update() {};

