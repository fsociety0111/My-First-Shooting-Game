#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Raycaster.h"
#include "Weapon.h"
#include "Enemy.h"

int main() 
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "MY FIRST SHOOTER"
    );

    Player player;
    Map map;
    Raycaster raycaster;

    // My WEAPONS
    Weapon weapon;
    weapon.load("resource/shotgun.png");

    // ============ THIS IS ENEMIES ======================
    /*raycaster.enemies = {
        Enemy(5.5f, 5.5f, "resource/enemy1.png"),
        Enemy(10.5f, 12.5f, "resource/enemy.png")
    };*/

    raycaster.enemies.emplace_back(
        std::make_unique<Enemy>(5.5f, 5.5f, "resource/enemy1.png")
    );

    raycaster.enemies.emplace_back(
        std::make_unique<Enemy>(10.5f, 13.5f, "resource/enemy.png")
    );

    bool isMoving = false;


    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // INPUT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.rotate(-1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.rotate(1);

        isMoving = false; // reset every frame

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(1, map);
            isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(-1, map);
            isMoving = true;
        }

        weapon.update(isMoving);

        window.clear();

        raycaster.render3D(window, player, map);      // walls
        raycaster.renderSprites(window, player);      // enemies
        raycaster.renderMiniMap(window, player, map); // minimap
        weapon.render(window);                         // weapon last

        window.display();
    }
    return 0;
}
