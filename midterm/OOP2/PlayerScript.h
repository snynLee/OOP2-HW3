#pragma once
#include "Component.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "IDamageable.h"

class PlayerScript :
    public Component, public IDamageable, public ICollidable
{
	float	hp;
	int		blink_period;

	bool slowDown;

	float speed;

	bool waiting;

	Position targetWorldPos;

public:

	PlayerScript(GameObject* gameObject);

	void setup(float hp) { this->hp = hp;  }
		
	float getHealth() const override { return hp; }
	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) gameObject->destroy();
		return getHealth();
	}

	void fireBullet();

	void update() override;

	void onCollision(GameObject* other) override;

};

