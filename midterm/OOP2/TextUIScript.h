#pragma once
#include "Component.h"
class Canvas;
class IDamageable;

class TextUIScript :
    public Component
{
	IDamageable* damageable;
	float	hp;
	int		n_remaining_frames;

public:
	TextUIScript(GameObject* gameObject);

	void setup(IDamageable* damageable) { this->damageable = damageable; }

	void update() override;
};

