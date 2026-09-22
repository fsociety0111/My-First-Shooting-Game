#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Bullet {
public:
    float x, y;
    float dx, dy;
    float speed = 10.0f;
    bool alive = true;

    Bullet(float px, float py, float angle) : x(px), y(py) {
        dx = std::cos(angle);
        dy = std::sin(angle);
    }

    void update(float dt, const Map& map) {
        if (!alive) return;
        x += dx * speed * dt;
        y += dy * speed * dt;

        if (map.isWall(x, y)) alive = false;
    }

    void renderMiniMap(sf::RenderWindow& window) const {
        const int scale = 10;
        const int pad = 10;
        sf::CircleShape dot(2);
        dot.setFillColor(sf::Color::Yellow);
        dot.setPosition(static_cast<float>(pad + x * scale - 1),
            static_cast<float>(pad + y * scale - 1));
        window.draw(dot);
    }
};
