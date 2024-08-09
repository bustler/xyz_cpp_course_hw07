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
	void DrawTop(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font);
	void EndGame(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font);
	void MainMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font);
	void GameSettingMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font);
	void PauseMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font);
	void WictoryMenu(Game& game, sf::Font& font, sf::RenderWindow& window, sf::Event& event);
}