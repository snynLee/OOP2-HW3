#pragma once
#include "GameObject.h"
#include "IDamageable.h"
#include "ICollidable.h"
#include "Utils.h"
#include "Canvas.h"

class Player;
class TextUI;

class Enemy : public GameObject, public IDamageable, public ICollidable {
	float	hp;
	float	dpf;

	int		nRemainingFire;

	// enemy-related functions

	float speed;

public:

	Enemy(GameObject* parent, const char* shape, const Position& pos, const Dimension& dim, float hp, float dpf);

	~Enemy()
	{}

	void move_automatically(const GameObject* player)
	{
		auto player_pos = player->getCenter();
		auto pos = getCenter();
		
		if (player_pos == pos) return;

		Direction dir = player_pos - pos;
		dir.normalize();
		move(dir * speed);
	}

	void update() override;

	float getHealth() const override { return hp; }

	float getDamaged(float damage) override {
		hp -= damage;
		if (hp <= 0.0f) 
			setDead();
		return getHealth();
	}

	void onCollision(GameObject* other) override;
};
