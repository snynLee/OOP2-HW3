#include "Canvas.h"
#include "Player.h"
#include "TextUI.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Wall.h"
#include "Transform.h"


Player::Player(GameObject* parent, const char* shape, const Position& pos, const Dimension& dim, float hp)
	: GameObject(parent, shape, pos, dim), 
	hp(hp), blink_period(-1), targetPos(Position::InvalidPos), speed(1.0f), slowDown(false), waiting(false)
{
	GameObject::Add(new TextUI(this, dim/2, {6, 1}));
}

void Player::onCollision(GameObject* other)
{
	if (dynamic_cast<Wall*>(other)) {
		setBack();
		invalidateTargetPos();
		return;
	}

	IDamageable* damageable = dynamic_cast<IDamageable*>(other);
	if (damageable == nullptr) return;

	damageable->getDamaged(0.1f);
}

void Player::update()
{
	if (inputManager->getKeyDown(VK_SPACE)) {
		fireBullet();
	}
	if (inputManager->getKey('A') || inputManager->getKey(VK_LEFT) ) {
		move(Vector2<float>::left);
	}
	if (inputManager->getKey('D') || inputManager->getKey(VK_RIGHT)) {
		move(Vector2<float>::right);
	}
	if (inputManager->getKey('W') || inputManager->getKey(VK_UP)) {
		move(Vector2<float>::up);
	}
	if (inputManager->getKey('S') || inputManager->getKey(VK_DOWN)) {
		move(Vector2<float>::down);
	}
	if (inputManager->getMouseButtonDown(0)) {
		waiting = true;
		speed = 1.0f;
		targetPos = inputManager->getMousePosition();
	}
	else if (inputManager->getMouseButton(0)) {
		if (waiting == true && targetPos != Position::InvalidPos) {
			waiting = false;
		}
		speed = speed + speed * 0.25f;
	}
	else if (inputManager->getMouseButtonUp(0)) {
		if (targetPos != Position::InvalidPos) {
			slowDown = true;
		}
		waiting = false;
	}

	if (slowDown == true) {
		if (speed == 1.0f) {
			slowDown = false;
		}
		else {
			speed = max(speed - speed * 0.25f, 1.0f);
		}
	}

	if (waiting == false && targetPos != Position::InvalidPos) {
		auto diff = (targetPos - getWorldPos());
		if (diff.sqrMagnitude() <= 1.0f) {
			move(diff);
			targetPos = Position::InvalidPos;
			speed = 1.0f;
		}
		else {
			auto dist = diff;
			dist.normalize();
			dist = dist * speed;
			move(dist > diff ? diff : dist);
		}
	}

	if (hp < 10.0f) {
		blink_period = (int)hp; // intentionally
		if (blink_period == 0) blink_period = 1;
	}
}

void Player::fireBullet()
{
	Bullet* bullet = new Bullet(this, this, true, getDimension()/2);
	GameObject::Add(bullet);

	GameObject* closestEnemy = GameObject::FindClosestTarget<Enemy>(this);
	if (closestEnemy) {
		bullet->init(this, closestEnemy);
		return;
	}
	
	auto screenPos = ScreenPosition{ canvas->getWidth() / 2, canvas->getHeight() / 2 };
	Position direction = Position{ (float)(rand() % canvas->getWidth()), (float)(rand() % canvas->getHeight()) } - screenPos;
	direction.normalize();
	bullet->init(this, direction);	
}

