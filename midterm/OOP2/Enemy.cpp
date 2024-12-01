#include "Enemy.h"
#include "Bullet.h"
#include "Canvas.h"
#include "Player.h"
#include "TextUI.h"
#include "Canvas.h"
#include "ExplodingBullet.h"
#include "Wall.h"

Enemy::Enemy(GameObject* parent, const char* shape, const Position& pos, const Dimension& dim, float hp, float dpf)
	: GameObject(parent, shape, pos, dim), hp(hp), dpf(dpf), nRemainingFire(rand() % 30), speed(1.0f)
{
	GameObject::Add(new TextUI(this, dim/2, { 6, 1 }));
}

void Enemy::onCollision(GameObject* other)
{
	if (dynamic_cast<Wall*>(other)) {
		setBack();
		return;
	}

	IDamageable* damageable = dynamic_cast<IDamageable*>(other);
	if (damageable == nullptr) return;

	// we assume enemies do not make any damage to their friend enemies
	if (dynamic_cast<Enemy*>(other) != nullptr) return;

	damageable->getDamaged(dpf);
}

void Enemy::update()
{
	if (inputManager->getKey('J')) {
		move(Vector2<float>::left);
	}
	if (inputManager->getKey('L')) {
		move(Vector2<float>::right);
	}
	if (inputManager->getKey('I')) {
		move(Vector2<float>::up);
	}
	if (inputManager->getKey('K')) {
		move(Vector2<float>::down);
	}

	// check whether it is time to attack.
	if (nRemainingFire > 0) {
		nRemainingFire--;
	}
	else if (nRemainingFire == 0) {		
		GameObject* player = GameObject::FindClosestTarget<Player>(this);
		Bullet* bullet = new ExplodingBullet(this, this, getDimension()/2);
		bullet->init(this, player);
		GameObject::Add(bullet);
		nRemainingFire = canvas->getFrameRate() * 5 + rand() % canvas->getFrameRate();
	}
}
