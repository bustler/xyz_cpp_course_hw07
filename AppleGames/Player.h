#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"
#include "GameStruct.h"
#include "Menu.h"

namespace ApplesGame
{
	void SetDirection(Game& game, sf::Event& event);
	void SetMovementInDirection(Game& game, float& deltaTime);
	void CheckCollision(Game& game, sf::RenderWindow& window, sf::Font& font, sf::Event& event);
}