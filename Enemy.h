#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Enemy {
public:
    float x, y;        // Map coordinates
    bool alive;
    sf::Texture texture;
    sf::Sprite sprite;

    Enemy(float _x, float _y, const std::string & texFile)
        : x(_x), y(_y), alive(true)
    {
        if (!texture.loadFromFile(texFile)) {
            std::cout << "Failed to load enemy texture: " << texFile << "\n";
        }
        else 
        {
            sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        }
    }

    void renderMiniMap(sf::RenderWindow& window, int scale = 10, int pad = 10) {
        if (!alive) return;
        sf::RectangleShape rect({ (float)scale, (float)scale });
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(pad + x * scale, pad + y * scale);
        window.draw(rect);
    }
};
