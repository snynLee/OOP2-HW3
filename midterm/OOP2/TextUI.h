#pragma once
#include "GameObject.h"

class Canvas;
class IDamageable;

class TextUI : public GameObject {
	IDamageable* damageable;
	float	hp;
	int		n_remaining_frames;
	
public:
	TextUI(GameObject* parent, const Position& pos, const Dimension& dim);

	void draw() override;
	
	void update() override;
};


