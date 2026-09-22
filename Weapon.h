#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Weapon {
public:
    sf::Texture texture;
    sf::Sprite sprite;

    float swayTime = 0.0f;

    bool load(const std::string& path) {
        if (!texture.loadFromFile(path))
            return false;

        sprite.setTexture(texture);
        return true;
    }

    void update(bool isMoving) {
        if (isMoving)
            swayTime += 0.1f;
        else
            swayTime *= 0.9f;
    }

    void render(sf::RenderWindow& window) {
        const float screenWidth =
            static_cast<float>(window.getSize().x);
        const float screenHeight =
            static_cast<float>(window.getSize().y);

        float scale =
            (screenWidth / texture.getSize().x) * 0.3f;

        sprite.setScale(scale, scale);

        // Sway offsets
        float swayX = std::sin(swayTime) * 10.0f;
        float swayY = std::abs(std::cos(swayTime)) * 5.0f;

        float x =
            screenWidth / 2.0f
            - sprite.getGlobalBounds().width / 2.0f
            + swayX;

        float y =
            screenHeight
            - sprite.getGlobalBounds().height
            + swayY;

        sprite.setPosition(x, y);

        window.draw(sprite);
    }
};
