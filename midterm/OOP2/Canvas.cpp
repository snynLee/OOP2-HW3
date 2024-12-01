#include "Canvas.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Renderer.h"


Canvas* Canvas::Instance = nullptr;

Canvas* Canvas::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new Canvas;
	}
	return Instance;
}

/*
void Canvas::draw(const GameObject* obj)
{
	if (obj == nullptr) return;

	draw(obj->getShape(), obj->getWorldPos(), obj->getDimension() );
}
*/


bool Canvas::isOutOfScreen(const GameObject* obj) const
{
	if (obj == nullptr) return false;

	auto transform = const_cast<GameObject*>(obj)->getComponent<Transform>();

	auto worldPos = transform->getLocal2World();
	auto pos = ScreenPosition(worldPos);

	auto endPos = ScreenPosition(pos + transform->getDimension());

	auto renderer = const_cast<GameObject*>(obj)->getComponent<Renderer>();

	if (endPos.x < 0 || pos.x >= width) {
		Debug::Log("%d out of screen", renderer->getShape());
		return true;
	}
	if (endPos.y < 0 || pos.y >= height) {
		Debug::Log("%d out of screen", renderer->getShape());
		return true;
	}

	return false;
}