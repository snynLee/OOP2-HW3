#include "GameObject.h"
#include "PlayerScript.h"
#include "Transform.h"
#include "Canvas.h"
#include "Renderer.h"
#include "BulletScript.h"
#include "EnemyScript.h"

PlayerScript::PlayerScript(GameObject* gameObject)
	: Component(gameObject), targetWorldPos(Position::InvalidPos),
	hp(0.0f), blink_period(-1), speed(1.0f), slowDown(false), waiting(false)
{}

void PlayerScript::onCollision(GameObject* other)
{
	/*
	auto wall = other->getComponent<WallScript>();
	if (wall) {
		
	}
	
	if (dynamic_cast<Wall*>(other)) {
		setBack();
		invalidateTargetPos();
		return;
	}*/

	IDamageable* damageable = other->getComponent<IDamageable>();
	if (damageable == nullptr) return;

	damageable->getDamaged(0.1f);
}

void PlayerScript::update()
{
	if (inputManager->getKeyDown(VK_SPACE)) {
		fireBullet();
	}
	if (inputManager->getKey('A') || inputManager->getKey(VK_LEFT)) {
		transform->move(Vector2<float>::left);
	}
	if (inputManager->getKey('D') || inputManager->getKey(VK_RIGHT)) {
		transform->move(Vector2<float>::right);
	}
	if (inputManager->getKey('W') || inputManager->getKey(VK_UP)) {
		transform->move(Vector2<float>::up);
	}
	if (inputManager->getKey('S') || inputManager->getKey(VK_DOWN)) {
		transform->move(Vector2<float>::down);
	}
	if (inputManager->getMouseButtonDown(0)) {
		waiting = true;
		speed = 1.0f;
		targetWorldPos = inputManager->getMousePosition();
	}
	else if (inputManager->getMouseButton(0)) {
		if (waiting == true && targetWorldPos != Position::InvalidPos) {
			waiting = false;
		}
		speed = speed + speed * 0.25f;
	}
	else if (inputManager->getMouseButtonUp(0)) {
		if (targetWorldPos != Position::InvalidPos) {
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

	if (waiting == false && targetWorldPos != Position::InvalidPos) {

		auto diff = (targetWorldPos - transform->getLocal2World());
		if (diff.sqrMagnitude() <= 1.0f) {
			transform->move(diff);
			targetWorldPos = Position::InvalidPos;
			speed = 1.0f;
		}
		else {
			auto dist = diff;
			dist.normalize();
			dist = dist * speed;
			transform->move(dist > diff ? diff : dist);
		}
	}

	if (hp < 10.0f) {
		blink_period = (int)hp; // intentionally
		if (blink_period == 0) blink_period = 1;
	}

	if (blink_period >= 0
		&& canvas->getCurrentFrameNumber() % blink_period == 0)
		renderer->setEnabled(false);
	else renderer->setEnabled(true);
	
}

void PlayerScript::fireBullet()
{
	auto bullet = new GameObject(this->gameObject, "*", 
		transform->getDimension() / 2, { 1, 1 });
	auto bulletScript = bullet->addComponent<BulletScript>();
	bulletScript->setup(this->gameObject);
	GameObject::Add(bullet);

	GameObject* closestEnemy = GameObject::FindClosestTarget<EnemyScript>(gameObject);
	if (closestEnemy) {
		bulletScript->init(this->gameObject, closestEnemy);
		return;
	}

	auto screenPos = ScreenPosition{ canvas->getWidth() / 2, canvas->getHeight() / 2 };
	Position direction = Position{ (float)(rand() % canvas->getWidth()), (float)(rand() % canvas->getHeight()) } - screenPos;
	direction.normalize();
	bulletScript->init(this->gameObject, direction);
}

