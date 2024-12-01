#pragma once

#include "Player.h"
#include "Component.h"
#include "Wall.h"


class WallManager : public Component
{
    vector<Wall*> walls;

    Player* player;

    Wall* current;

    Position originalPos;

    bool collidingOtherWall(Transform* wall) const;

public:
    WallManager(GameObject* gameObject, Player* player) : 
        Component(gameObject) , player(player), current(nullptr), originalPos(Position::InvalidPos)
    {}

    ~WallManager() { walls.clear(); }
    
    // void draw() override { return;  }

    void update() override;
};
