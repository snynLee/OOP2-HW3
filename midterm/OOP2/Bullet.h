#pragma once
#include "GameObject.h"
#include "ICollidable.h"
#include "IDamageable.h"
#include "Canvas.h"

class Bullet : public GameObject, public ICollidable, public IDamageable {

	bool	penetrable;

	GameObject* from;

	float	speed;

	float	hp;

	
public:

	Bullet(GameObject* parent, GameObject* from, bool penetrable = false, const Position& pos = { 0.0f, 0.0f }, const Dimension& dim = { 1,1 })
		: GameObject(parent, nullptr, pos, dim), penetrable(penetrable), speed(1.0f), from(from), hp{1000000.f}
	{}

	~Bullet()
	{}

	void update() override;

	void init(const GameObject* from, Direction heading)
	{	
		setPos( from->getDimension()/2 );
		setDirection(heading);
		setShape("*");
	}

	void init(const GameObject* from, const GameObject* to)
	{
		auto toPos = to->getWorldPos() + to->getDimension()/2;
		auto pos = from->getWorldPos() + from->getDimension()/2;
		auto centerScreen = ScreenPosition(canvas->getWidth() / 2, canvas->getHeight() / 2);
		auto direction = Position((float)(rand() % canvas->getWidth()), (float)(rand() % canvas->getHeight())) - centerScreen;
		if (!(pos == toPos)) direction = toPos - pos;
		direction.normalize();
		init(from, direction);
	}
	
	void onCollision(GameObject* other) override;

	float getHealth() const override { return hp; }
	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) setDead();
		return getHealth();
	}

	float getSpeed() { return speed; }
};


