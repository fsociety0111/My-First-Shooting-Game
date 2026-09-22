#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Raycaster.h"
#include "Weapon.h"
#include "Enemy.h"

class Game 
{
public:
	Game();
	void run();

private:
	// window
	sf::RenderWindow window;
	sf::Clock deltaclock;

	// Game objects
	Player player;
	Enemy enemies;
	Weapon weapons;
	Map map;
	Raycaster reycaster;

	// Core functions
	void processEvents();
	void update();
};
