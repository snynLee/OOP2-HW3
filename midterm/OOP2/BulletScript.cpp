
#include "GameObject.h"
#include "BulletScript.h"
#include "IDamageable.h"
#include "Canvas.h"
#include "Renderer.h"


void BulletScript::onCollision(GameObject* other)
{
	/*
	if (dynamic_cast<Wall*>(other)) {
		setDead();
		return;
	}
	*/

	IDamageable* damageable = other->getComponent<IDamageable>();
	if (damageable == nullptr) return;

	if (other == from) return;

	damageable->getDamaged(5.0f);
	gameObject->destroy();
}

void BulletScript::update()
{
	if (canvas->isOutOfScreen(this->gameObject)) {
		gameObject->destroy();
		return;
	}

	auto dir = transform->getDirection();
	transform->move(dir * speed);
}

void BulletScript::init(GameObject* from, Direction heading)
{
	auto fromTransform = from->getComponent<Transform>();
	transform->setPosition(fromTransform->getDimension() / 2);
	transform->setDirection(heading);
	renderer->setShape("*");
}

void BulletScript::init(GameObject* from, GameObject* to)
{
	auto fromTransform = from->getComponent<Transform>();
	auto toTransform = to->getComponent<Transform>();
	auto toPos = toTransform->getLocal2World() + toTransform->getDimension() / 2;
	auto pos = fromTransform->getLocal2World() + fromTransform->getDimension() / 2;
	auto centerScreen = ScreenPosition(canvas->getWidth() / 2, canvas->getHeight() / 2);
	auto direction = Position((float)(rand() % canvas->getWidth()), (float)(rand() % canvas->getHeight())) - centerScreen;
	if (!(pos == toPos)) direction = toPos - pos;
	direction.normalize();
	init(from, direction);
}
