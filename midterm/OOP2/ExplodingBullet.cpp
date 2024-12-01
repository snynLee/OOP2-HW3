#include "ExplodingBullet.h"

void ExplodingBullet::update()
{
	if (--nRemainingFrames <= 0) {
		setDead();
		return;
	}
	auto dir = getDirection();
	move(dir * getSpeed() );
}
