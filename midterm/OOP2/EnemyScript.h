#pragma once
#include "Component.h"
#include "GameObject.h"
#include "IDamageable.h"
#include "ICollidable.h"
#include "Utils.h"
#include "Canvas.h"

class PlayerScript;
class TextUIScript;

class EnemyScript :
    public Component, public IDamageable, public ICollidable 
{
	float	hp;
	float	dpf;

	int		nRemainingFire;

	float	speed;

public:

	EnemyScript(GameObject* gameObject)
		: Component(gameObject),
		hp(0.0f), dpf(0.0f), nRemainingFire(rand() % 30), speed(1.0f)
	{}

	void setup(float hp, float dpf) { this->hp = hp; this->dpf = dpf; }

	void update() override;

	float getHealth() const override { return hp; }

	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f)
			gameObject->destroy();
		return getHealth();
	}

	void onCollision(GameObject* other) override;

};

