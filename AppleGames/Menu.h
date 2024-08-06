#pragma once
#include "GameStruct.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct MenuInfo
	{
		sf::Text time;
		sf::Text score;
	};

	MenuInfo ShowInfo(sf::Font& font);
	void EndGame(sf::RenderWindow& window, sf::Font& font, sf::Event& event, bool& triggerEndGame, Game& game);
	void GameSettingMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font, bool& triggerEndGame);
	void WictoryMenu(Game& game, sf::Font& font, sf::RenderWindow& window, sf::Event& event);
}