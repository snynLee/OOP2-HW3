#pragma once
class GameObject;

class ICollidable
{
public:
	virtual void onCollision(GameObject* other) = 0;

};

