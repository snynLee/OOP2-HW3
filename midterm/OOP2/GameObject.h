#pragma once

#include "Utils.h"
#include "InputManager.h"
#include "Transform.h"
#include "Renderer.h"
#include <vector>
#include <algorithm>

class Canvas;
class Component;


using namespace std;

class GameObject {

	bool	active;

protected:

	friend class Component;

	static vector<GameObject*> Objects;
	static vector<GameObject*> PendingObjects;

	Canvas*				canvas;
	InputManager*		inputManager;
	
	vector<Component*>	components;
	Transform*			transform;
	Renderer*			renderer;

	vector<GameObject*> children;
	GameObject*			parent;
	vector<GameObject*> pendingChildren;

	

	void addChild(GameObject* child)
	{
		if (child != nullptr) children.push_back(child);
	}

	void removeChild(GameObject* child)
	{
		if (child) pendingChildren.push_back(child);
	}

	void internalUpdate(const Position& parentWorldPos);
	
public:


	template<typename T>
	T* addComponent()
	{
		T* component = new T(this);
		components.push_back(component);

		return component;
	}

	template<typename T>
	T* getComponent() const
	{
		for (auto component : components)
		{
			T* comp = dynamic_cast<T*>(component);
			if (comp != nullptr) return comp;
		}
		return nullptr;
	}

	template<typename T>
	T* getOrAddComponent()
	{
		auto comp = getComponent<T>();
		if (comp == nullptr) {
			comp = addComponent<T>();
		}
		return comp;
	}

	static void Init(int size);
	static void Destroy();
	static void Add(GameObject* obj);
	static void Remove(GameObject* obj);
	static bool Contains(GameObject* obj);

	template<typename T>
	static GameObject* FindClosestTarget(const GameObject* source)
	{
			GameObject* closest = nullptr;
			if (source == nullptr) return closest;

			auto srcTransform = source->transform;

			float closestDistance = 0;
			for (auto obj : Objects) {

				auto target = obj->getComponent<T>();
				if (target == nullptr) continue;

				auto targetTransform = target->transform;
				float dist = (srcTransform->getLocal2World() - targetTransform->getLocal2World()).sqrMagnitude();
				if (closest == nullptr || dist < closestDistance ) {
					closest = obj;
					closestDistance = dist;
				}
			}
			return closest;
	}

	static bool Update();

	GameObject(GameObject* parent, 
		const char* str, 
		const Position& pos, const Dimension& dim, const Direction& dir = Direction{0, 0});

	virtual ~GameObject()
	{
		while (components.empty() == false) {
			auto back = components.back();
			delete back;
			components.pop_back();
		}

		children.clear();
	}

	/*void setVisible(bool visible = true)
	{
		renderer->setEnabled(visible);
	}*/

	void setActive(bool active = true)
	{
		this->active = active;
	}

	bool isActive() const { return active; }

	void destroy() 
	{ 
		setActive(false);
		for (auto child : children)
			child->setActive(false);
		if (parent) parent->removeChild(this);
		parent = nullptr;
	}
		
	GameObject* getParent() const { return parent; }

	void setParent(GameObject* newParent) { parent = newParent; }
		
};



