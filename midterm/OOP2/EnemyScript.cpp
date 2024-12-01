#include "GameObject.h"
#include "EnemyScript.h"
#include "PlayerScript.h"
//#include "TextUIScript.h"
#include "Canvas.h"
#include "BulletScript.h"


void EnemyScript::onCollision(GameObject* other)
{
	IDamageable* damageable = other->getComponent<IDamageable>();
	if (damageable == nullptr) return;

	if (other->getComponent<EnemyScript>()) return;

	damageable->getDamaged(dpf);
}

void EnemyScript::update()
{
	if (inputManager->getKey('J')) {
		transform->move(Vector2<float>::left);
	}
	if (inputManager->getKey('L')) {
		transform->move(Vector2<float>::right);
	}
	if (inputManager->getKey('I')) {
		transform->move(Vector2<float>::up);
	}
	if (inputManager->getKey('K')) {
		transform->move(Vector2<float>::down);
	}

	// check whether it is time to attack.
	if (nRemainingFire > 0) {
		nRemainingFire--;
	}
	else if (nRemainingFire == 0) {
		auto player = GameObject::FindClosestTarget<PlayerScript>(this->gameObject);

		auto bullet = new GameObject(this->gameObject, "*",
			transform->getDimension() / 2, { 1, 1 });
		auto bulletScript = bullet->addComponent<BulletScript>();
		bulletScript->setup(this->gameObject);
		GameObject::Add(bullet);
		
		bulletScript->init(this->gameObject, player);
		nRemainingFire = canvas->getFrameRate() * 5 + rand() % canvas->getFrameRate();
	}
}