#pragma once
#include "Component.h"
#include "Vector2.h"

class GameObject;


class Transform :
    public Component
{
    Position		position;
    Dimension	dimension;
    Direction	direction;

    Position		parentWorldPos;

public:
	Transform(GameObject* gameObject);

	void setup(const Position& pos, const Dimension& dim, const Direction& dir);

	void move(const Position& inc)
	{
		setPosition(getPosition() + inc);
	}

	void setParentWorldPos(const Position& parentWorldPos) {
		this->parentWorldPos = parentWorldPos;
	}

    Position getPosition() const { return position; }
	Position getEndPosition() const { return position + dimension; }
	Position getCenterPosition() const 
	{ return (getPosition() * 2 + getDimension() ) / 2; }

	void setPosition(const Position& pos) { this->position = pos; }

	Position getLocal2World() const { return parentWorldPos + position; }
	Position getWorld2Local(const Position& worldPos) const {
		return worldPos - parentWorldPos;
	}    

    Dimension getDimension() const { return dimension; }
    void setDimension(const Dimension& dim) { this->dimension = dim; }
	    
	Direction getDirection() const { return direction; }
    void setDirection(const Direction& direction) { this->direction = direction; }

    auto getDimensionSize() const { return dimension.x * dimension.y; }

	bool isOverlap(const GameObject* other) const;
	bool isOverlap(const Position& loc) const;

	// 충돌체 존재 여부 판정 후, 이동하는 기능
	bool isOverlapping(const Position& from, const Position& to);
};

