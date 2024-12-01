#pragma once

class GameObject;
class Transform;
class Renderer;
class Canvas;
class InputManager;

class Component
{

	bool enabled;


protected:

	friend class GameObject;

	

	Canvas* canvas;
	InputManager* inputManager;

	Transform* transform;
	Renderer* renderer;
	GameObject* gameObject;
	
public:

	

	Component(GameObject* gameObject);

	virtual ~Component() {}

	virtual void start() {}

	virtual void update() {}

	void setEnabled(bool enabled = true) { this->enabled = enabled; }

	bool isEnabled() const { return this->enabled; }



};

