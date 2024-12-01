#include "GameObject.h"
#include "Transform.h"

Transform::Transform(GameObject* gameObject) : Component(gameObject)
{	
}

void Transform::setup(const Position& pos,
	const Dimension& dim,
	const Direction& dir)
{
	this->transform = this;
	this->renderer = gameObject->getComponent<Renderer>();

	this->position = pos;
	this->dimension = dim;
	this->direction = dir;

	auto parent = gameObject->getParent();
	if (parent) {
		auto parentTransform = parent->getComponent<Transform>();
		this->parentWorldPos = parentTransform->getLocal2World();
	}
	else {
		this->parentWorldPos = { 0, 0 };
	}

}


bool Transform::isOverlap(const GameObject* other) const
{
	if (other == nullptr) return false;

	/*
	auto pos = getLocal2World();
	auto endPos = pos + getDimension();

	auto otherTransform = other->getComponent<Transform>();
	if (otherTransform == nullptr) return false;

	auto otherPos = otherTransform->getLocal2World();
	auto otherEndPos = otherPos + otherTransform->getDimension();

	*/

	auto pos = getPosition();
	auto endPos = getEndPosition();

	auto otherTransform = other->getComponent<Transform>();
	if (otherTransform == nullptr) return false;

	auto otherPos = getWorld2Local(otherTransform->getLocal2World());
	auto otherEndPos = getWorld2Local(otherTransform->getLocal2World() + otherTransform->getDimension());


	if (endPos.y < otherPos.y || otherEndPos.y < pos.y) return false;
	if (endPos.x < otherPos.x || otherEndPos.x < pos.x) return false;

	return true;
}

bool Transform::isOverlap(const Position& worldPos) const
{
	auto pos = getLocal2World();
	auto endPos = pos + getDimension();

	return (worldPos.x >= pos.x && worldPos.x < endPos.x) && (worldPos.y >= pos.y && worldPos.y < endPos.y);
}

bool Transform::isOverlapping(const Position& from, const Position& to)
{
	return isOverlap(from) || isOverlap(to);
}
