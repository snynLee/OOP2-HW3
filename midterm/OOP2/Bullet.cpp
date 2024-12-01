#include "Bullet.h"
#include "IDamageable.h"
#include "Canvas.h"
#include "Wall.h"

void Bullet::onCollision(GameObject* other)
{
	if (dynamic_cast<Wall*>(other)) {
		setDead();
		return;
	}

	IDamageable* damageable = dynamic_cast<IDamageable*>(other);
	if (damageable == nullptr) return;

	if (other == from) return;

	damageable->getDamaged(5.0f);
	setDead();
}

void Bullet::update() 
{
	if (canvas->isOutOfScreen(this)) {
		setDead();
		return;
	}
	
	auto dir = getDirection();
	move(dir * speed);
}