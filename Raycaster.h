#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <cmath>
#include "Player.h"
#include "Map.h"
#include "Enemy.h"

constexpr float FOV = 3.14159f / 3.0f; // 60 degrees

class Raycaster {
public:
    int screenWidth = 800;
    int screenHeight = 600;
    std::vector<float> depthBuffer;
    std::vector<std::unique_ptr<Enemy>> enemies;

    Raycaster() { depthBuffer.resize(screenWidth); }

    void render3D(sf::RenderWindow& window, const Player& player, const Map& map) {
        for (int x = 0; x < screenWidth; ++x) {
            float rayAngle = (player.angle - FOV / 2.0f) + (x / (float)screenWidth) * FOV;
            float rayX = std::cos(rayAngle);
            float rayY = std::sin(rayAngle);

            float distance = 0.0f;
            bool hit = false;
            while (!hit && distance < 20.0f) {
                distance += 0.05f;
                float testX = player.x + rayX * distance;
                float testY = player.y + rayY * distance;
                if (map.isWall(testX, testY)) hit = true;
            }

            float wallHeight = (float)screenHeight / distance;
            float drawStart = screenHeight / 2.0f - wallHeight / 2.0f;
            float drawEnd = drawStart + wallHeight;

            sf::Vertex line[] = {
                sf::Vertex({(float)x, drawStart}, sf::Color::White),
                sf::Vertex({(float)x, drawEnd}, sf::Color::White)
            };

            window.draw(line, 2, sf::Lines);
            depthBuffer[x] = distance;
        }
    }

    void renderMiniMap(sf::RenderWindow& window, const Player& player, const Map& map) {
        const int scale = 10;
        const int pad = 10;

        // Draw walls
        for (int y = 0; y < map.height(); ++y) {
            for (int x = 0; x < map.width(); ++x) {
                sf::RectangleShape tile({ (float)scale, (float)scale });
                tile.setPosition((float)(pad + x * scale), (float)(pad + y * scale));
                tile.setFillColor(map.grid[y][x] == '1' ? sf::Color::White : sf::Color(50, 50, 50));
                window.draw(tile);
            }
        }

        // Draw enemies
        for (auto& e : enemies) e->renderMiniMap(window);

        // Draw player
        sf::CircleShape dot(scale / 2.0f);
        dot.setFillColor(sf::Color::Red);
        dot.setPosition(pad + player.x * scale - scale / 4.0f,
            pad + player.y * scale - scale / 4.0f);
        window.draw(dot);
    }

    void renderSprites(sf::RenderWindow& window, const Player& player) {
        float screenW = (float)window.getSize().x;
        float screenH = (float)window.getSize().y;

        for (const auto& spriteObj : enemies) {
            if (!spriteObj->alive) continue;

            float dx = spriteObj->x - player.x;
            float dy = spriteObj->y - player.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            // Skip extremely close or far enemies
            if (distance < 0.01f) continue;

            float angleToSprite = std::atan2(dy, dx) - player.angle;
            while (angleToSprite > 3.14159f) angleToSprite -= 2.0f * 3.14159f;
            while (angleToSprite < -3.14159f) angleToSprite += 2.0f * 3.14159f;

            if (std::abs(angleToSprite) < FOV / 2.0f) {
                float spriteScreenX = (0.5f + angleToSprite / FOV) * screenW;
                float spriteHeight = screenH / distance;

                sf::Sprite sprite = spriteObj->sprite;
                sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f,
                    sprite.getTexture()->getSize().y / 2.0f);
                sprite.setScale(spriteHeight / sprite.getTexture()->getSize().y,
                    spriteHeight / sprite.getTexture()->getSize().y);
                //sprite.setPosition(spriteScreenX, screenH / 2.0f - spriteHeight / 2.0f);
                sprite.setPosition(spriteScreenX, screenH / 2.0f);

                int column = (int)spriteScreenX;
                if (column >= 0 && column < depthBuffer.size() && distance < depthBuffer[column])
                    window.draw(sprite);
            }
        }
    }
};
