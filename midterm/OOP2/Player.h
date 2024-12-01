#pragma once
#include "GameObject.h"
#include "Canvas.h"
#include "IDamageable.h"
#include "ICollidable.h"

class TextUI;

class Player : public GameObject, public IDamageable, public ICollidable {

	float	hp;
	int		blink_period;

	Position targetPos;

	bool slowDown;

	float speed;

	bool waiting;

public:

	Player(GameObject* parent, const char* shape, const Position& pos, const Dimension& dim, float hp);

	~Player()
	{}

	void invalidateTargetPos() { targetPos = Position::InvalidPos; speed = 1.0f; waiting = false; }

	float getHealth() const override { return hp; }
	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) setDead();
		return getHealth();
	}

	void draw() override
	{
		if (blink_period >= 0
			&& canvas->getCurrentFrameNumber() % blink_period == 0)
			return;

		GameObject::draw();
	}

	void move(const Position& inc)
	{
		setPos(getPos() + inc);
	}
	
	void fireBullet();

	void update() override;

	void onCollision(GameObject* other) override;
};


