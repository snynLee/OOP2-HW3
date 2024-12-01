#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"
#include "Canvas.h"
#include "InputManager.h"


Component::Component(GameObject* gameObject) 
	: gameObject(gameObject), enabled(true),
	transform(gameObject->transform), renderer(gameObject->renderer),
	canvas( Canvas::GetInstance() ),
	inputManager( InputManager::GetInstance() )
{
	start();
}