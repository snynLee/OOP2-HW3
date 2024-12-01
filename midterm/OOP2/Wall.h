#pragma once
#include "GameObject.h"
#include "Player.h"

class Wall :
    public GameObject, public ICollidable
{
	bool valid;
	
public:
	Wall(GameObject* parent, const Position& pos, const Dimension& dim);

	void changeDimension(const Dimension& dim) {

		transform->setDimension(dim);

		auto shape = new char[dim.x * dim.y + 1];
		memset(shape, '@', dim.x * dim.y);
		shape[dim.x * dim.y] = '\0';
		renderer->setShape(shape);
		delete[] shape;
	}

	void setValid(bool valid=true) { this->valid = valid; }
	
	void draw();

	// void update() override;

	void onCollision(GameObject* other) {}

};

