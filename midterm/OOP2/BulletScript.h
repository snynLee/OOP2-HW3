#pragma once
#include "GameObject.h"
#include "Component.h"
#include "ICollidable.h"
#include "IDamageable.h"


class BulletScript :
    public Component, public ICollidable, public IDamageable
{
	bool	penetrable;

	GameObject* from;

	float	speed;

	float	hp;


public:

	BulletScript(GameObject* gameObject) 
		: Component(gameObject), from(nullptr), penetrable(false), speed(1.0f), hp(100000.f)
	{}
		
		
		
	void setup(GameObject* from)
	{
		this->from = from;
	}

	void update() override;

	void init(GameObject* from, Direction heading);

	void init(GameObject* from, GameObject* to);

	void onCollision(GameObject* other) override;

	float getHealth() const override { return hp; }
	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) gameObject->destroy();
		return getHealth();
	}

	float getSpeed() { return speed; }


};

