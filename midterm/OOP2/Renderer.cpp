#include "GameObject.h"
#include "Renderer.h"
#include "Canvas.h"
#include "Transform.h"


void Renderer::setup(const char* str)
{
	this->transform = gameObject->getComponent<Transform>();
	this->renderer = this;

	setShape(str);
}

void Renderer::setShape(const char* str)
{
	if (str == nullptr) {
		if (this->shape != nullptr) {
			delete[] this->shape;
			this->shape = nullptr;
		}
		return;
	}

	if (this->shape != nullptr) {
		delete[] this->shape;
		this->shape = nullptr;
	}
	auto sz = transform->getDimensionSize() > strlen(str) ? 
		strlen(str) : transform->getDimensionSize() ;
	this->shape = new char[sz + 1];
	strncpy(this->shape, str, sz);
	this->shape[sz] = '\0';
}

const char* Renderer::getShape() const { return this->shape; }


void Renderer::update()
{
	canvas->draw(shape, transform->getLocal2World(), transform->getDimension());
}