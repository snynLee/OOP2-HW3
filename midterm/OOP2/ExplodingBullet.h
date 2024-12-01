#pragma once
#include "Bullet.h"
#include "Canvas.h"

class ExplodingBullet :
    public Bullet
{
	int nRemainingFrames;

public:

	ExplodingBullet(GameObject* parent, GameObject* from, const Position& pos = { 0.0f, 0.0f }, const Dimension& dim = { 1,1 })
		: Bullet(parent, from, false, pos, dim), nRemainingFrames(1* Canvas::GetInstance()->getFrameRate())
	{}

	~ExplodingBullet()
	{}

	void update() override;
};

