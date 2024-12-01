#pragma once
#include "Component.h"
class Renderer :
    public Component
{
    char* shape;

public:
    Renderer(GameObject* gameObject) : Component(gameObject), shape(nullptr) {}

    void setup(const char* str);

    const char* getShape() const;
    void setShape(const char* str);


    void update() override;
};

