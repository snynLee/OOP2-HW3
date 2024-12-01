#include "WallManager.h"


bool WallManager::collidingOtherWall(GameObject* wall) const {
	for (auto other : walls) {
		if (other == wall) continue;
		if (other->isOverlap(wall)) return true;
	}
	return false;
}

void WallManager::update()
{
	if (inputManager->getMouseButtonDown(1)) {
		auto pos = inputManager->getMousePosition();

		auto dim = Dimension(rand() % 3 + 1, rand() % 3 + 1);

		Wall* newWall = new Wall(this, pos, dim);
		newWall->changeDimension(dim);

		int numTrials = 20;
		while (numTrials-- >= 0) {

			auto colliding = collidingOtherWall(newWall);
			if (colliding == true) {
				newWall->changeDimension(Dimension(rand() % 3 + 1, rand() % 3 + 1));
				continue;
			}
			GameObject::Add(newWall);
			walls.push_back(newWall);
			break;
		}
		if (numTrials < 0) {
			delete newWall;
		}
	}
	if (inputManager->getMouseButtonDown(0)) {
		auto pos = inputManager->getMousePosition();

		Wall* target = nullptr;
		for (auto wall : walls) {
			if (wall->isOverlap(pos)) {
				target = wall;
				break;
			}
		}
		if (target) {
			originalPos = target->getPos();
			current = target;
			player->invalidateTargetPos();
		}
	}
	if (inputManager->getMouseButton(0)) {
		auto pos = inputManager->getMousePosition();
		if (current) {
			auto colliding = collidingOtherWall(current);
			current->setPos(pos);
			current->setValid(colliding == false);
		}
	}
	if (inputManager->getMouseButtonUp(0)) {
		auto pos = inputManager->getMousePosition();
		if (current) {
			auto colliding = collidingOtherWall(current);
			current->setPos(colliding == true ? originalPos : pos);
			current->setValid(true);
			originalPos = Position::InvalidPos;
			current = nullptr;
		}
	}
}
