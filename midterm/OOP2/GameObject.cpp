#include "GameObject.h"
#include "Canvas.h"
#include "ICollidable.h"
//#include "WallManager.h"
#include "Transform.h"
#include "Renderer.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
#include "TextUIScript.h"


vector<GameObject*> GameObject::Objects;
vector<GameObject*> GameObject::PendingObjects;

GameObject::GameObject(GameObject* parent, 
	const char* str, 
	const Position& pos, const Dimension& dim, const Direction& dir)
	: canvas(Canvas::GetInstance()), inputManager(InputManager::GetInstance()), 
	active(true), parent(parent)
{
	this->transform = addComponent<Transform>();
	this->renderer = addComponent<Renderer>();

	this->transform->setup(pos, dim, dir);	
	this->renderer->setup(str);	
}


void GameObject::internalUpdate(const Position& parentWorldPos)
{
	while (pendingChildren.size()) {
		auto child = pendingChildren.back();
		auto it = find(children.begin(), children.end(), child);
		if (it != children.end()) children.erase(it);
		pendingChildren.pop_back();
	}

	transform->setParentWorldPos(parentWorldPos);
	if (isActive() == false) return;
	for (auto component : components) {
		if (isActive() == false) break;
		if (component->isEnabled() == false) continue;
		component->update();
	}

	for (auto it = children.begin(); it != children.end(); it++) {
		auto child = *it;
		if (isActive() == false) break;
		if (child->isActive() == false) continue;
		child->internalUpdate(transform->getLocal2World());
	}
}

void GameObject::Init(int size = 10)
{
	auto canvas = Canvas::GetInstance();

	auto player = new GameObject(nullptr, "E   E      - -  --- C   C", { 10, 10 }, { 5, 5 });
	auto playerScript = player->addComponent<PlayerScript>();
	playerScript->setup(10000.0f);
	auto playerHpUI = new GameObject(player, "      ", player->transform->getDimension() / 2, { 6,1 } );
	auto playerHpUIScript = playerHpUI->addComponent<TextUIScript>();
	playerHpUIScript->setup(playerScript);

	auto enemy = new GameObject(nullptr, " ____ (+*_*) ---- ", { 50, 5 }, { 6, 3 });
	auto enemyScript = enemy->addComponent<EnemyScript>();
	enemyScript->setup(50.0f, 10.0f / Canvas::GetInstance()->getFrameRate());
	auto enemyHpUI = new GameObject(enemy, "      ", enemy->transform->getDimension() / 2, { 6,1 });
	auto enemyHpUIScript = enemyHpUI->addComponent<TextUIScript>();
	enemyHpUIScript->setup(enemyScript);

	Add(playerHpUI); Add(player);
	Add(enemyHpUI); Add(enemy);
	
	//auto wallManager = new GameObject(nullptr);
	//wallManager->addComponent<WallManagerScript>();

	//Add(wallManager);
	/*
	Add(new WallManager(player));
	*/
}

void GameObject::Destroy()
{
	while (PendingObjects.empty() == false) {
		auto obj = PendingObjects.back();
		delete obj;
		PendingObjects.pop_back();
	}
	while (Objects.empty() == false) {
		auto obj = Objects.back();
		delete obj;
		Objects.pop_back();
	}
}

void GameObject::Add(GameObject* obj)
{
	if (obj == nullptr) return;
	PendingObjects.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	auto it = find(Objects.begin(), Objects.end(), obj);
	if (it != Objects.end())
		Objects.erase(it);
	delete obj;
}

bool GameObject::Contains(GameObject* obj)
{
	auto it = find(Objects.cbegin(), Objects.cend(), obj);
	return it != Objects.cend();
}



bool GameObject::Update()
{
	auto inputManager = InputManager::GetInstance();
	auto canvas = Canvas::GetInstance();

	if (inputManager->getKeyDown('Q') || inputManager->getKeyDown(VK_ESCAPE)) {
		return false;
	}
	if (inputManager->getMouseButtonUp(1)) {
		auto enemy = new GameObject(nullptr, " ____ (+*_*) ---- ", { (float)(rand() % canvas->getWidth()), (float)(rand() % canvas->getHeight()) }, { 6, 3 });
		auto enemyScript = enemy->addComponent<EnemyScript>();
		enemyScript->setup(50.0f, 10.0f / Canvas::GetInstance()->getFrameRate());
		auto enemyHpUI = new GameObject(enemy, "      ", enemy->transform->getDimension() / 2, { 6,1 });
		auto enemyHpUIScript = enemyHpUI->addComponent<TextUIScript>();
		enemyHpUIScript->setup(enemyScript);
		
		Add(enemyHpUI); Add(enemy);
	}

	
	// it traverses all objects along the hierarchical path
	for (auto obj : Objects) {
		if (obj->getParent()) continue;
		obj->internalUpdate({ 0, 0 });
	}

	// collision check
	for (auto obj : Objects) {

		auto collidable = obj->getComponent<ICollidable>();
		if (collidable == nullptr || obj->isActive() == false) continue;

		for (auto other : Objects) {
			if (other == obj) break;

			if (obj->isActive() == false) continue;

			auto collided = other->getComponent<ICollidable>();
			if (collided == nullptr 
				|| other->isActive() == false 
				|| obj->transform->isOverlap(other) == false ) 
				continue;

			collided->onCollision(obj);
			collidable->onCollision(other);
		}
	}

	// remove dying objects
	for (auto it = Objects.begin(); it != Objects.end(); )
	{
		auto obj = *it;
		if (obj->isActive()) {
			it++;
			continue;
		}

		delete obj;
		it = Objects.erase(it);
	}


	// add pending objects to regular objects
	while (PendingObjects.empty() == false) {
		auto obj = PendingObjects.back();
		PendingObjects.pop_back();
		Objects.push_back(obj);
		auto parent = obj->getParent();
		if (parent) parent->addChild(obj);
	}

	return true;
}