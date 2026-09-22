#include "Game.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <algorithm>
#include <cmath>

Game::Game() 
	:window(sf::VideoMode(800, 600), "My first shooter")
{
}