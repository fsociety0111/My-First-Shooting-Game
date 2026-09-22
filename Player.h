#pragma once
#include <cmath>
#include "Map.h"

class Player 
{
public:
    float x = 3.5f;
    float y = 3.5f;
    float angle = 0.0f;

    float moveSpeed = 0.07f;
    float rotSpeed = 0.07f;
    float radius = 0.2f;

    void rotate(float dir) 
    {
        angle += dir * rotSpeed;
    }

    void move(float dir, const Map& map) 
    {
        float nextX = x + cos(angle) * moveSpeed * dir;
        float nextY = y + sin(angle) * moveSpeed * dir;

        if (!collides(nextX, y, map))
            x = nextX;
        if (!collides(x, nextY, map))
            y = nextY;
    }

private:
    bool collides(float nx, float ny, const Map& map) 
    {
        return map.isWall(nx + radius, ny) ||
            map.isWall(nx - radius, ny) ||
            map.isWall(nx, ny + radius) ||
            map.isWall(nx, ny - radius);
    }
};
