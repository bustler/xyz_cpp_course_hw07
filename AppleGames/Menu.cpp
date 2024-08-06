#include "Menu.h"
#include "Constants.h"
#include "GameStruct.h"
#include "Math.h"
#include <SFML/Audio.hpp>
#include <sys/_types/_size_t.h>
#include <cstdint>


void DrawBorderMenu(ApplesGame::Vector2D sizeOfWindow, sf::RenderWindow& window)
{
	float x = sizeOfWindow.x - 20;
	float y = sizeOfWindow.y - 20;
	sf::RectangleShape border[8];//border1x, border2x, border3x, border4x, border5x, border1y, border2y, border3y;
	for(size_t i = 0; i < 5; i++) //draw vertical borders
	{
		border[i].setSize(sf::Vector2f(10, y));
		border[i].setFillColor(sf::Color::White);
		border[i].setPosition((x / 4) * i + 5, 5);
		window.draw(border[i]);
	}
	for(size_t i = 5; i < 8; i++) //draw horizontal borders
	{
		border[i].setSize(sf::Vector2f(x + 10, 10));
		border[i].setFillColor(sf::Color::White);
		border[i].setPosition(5, (y / 2) * (i - 5) + 5);
		window.draw(border[i]);
	}
}

void DrawText(sf::String text, sf::Font& font, ApplesGame::Vector2D coordinateOfWindow, sf::RenderWindow& window)
{
	sf::Text item;
	item.setFont(font);
	item.setCharacterSize(20);
	item.setFillColor(sf::Color::White);
	item.setPosition(coordinateOfWindow.x, coordinateOfWindow.y);
	item.setString(text);
	window.draw(item);
}

void SelectionButtons(bool (&selector)[2][4], ApplesGame::Vector2D sizeOfWindow, sf::RenderWindow& window, sf::Event& event, ApplesGame::Game& game)
{
	float x = sizeOfWindow.x - 20;
	float y = sizeOfWindow.y - 20;
	sf::RectangleShape cursor[2][4];
	sf::RectangleShape lines;
	for(size_t i = 0; i < 2; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{

			// Draw cursor
			if(selector[i][j])
			{
				cursor[i][j].setSize(sf::Vector2f(200, 80));
				cursor[i][j].setFillColor(sf::Color::Red);
				cursor[i][j].setPosition(50 +(x / 4 * j), 200 + (y / 2 * i));
				window.draw(cursor[i][j]);

				if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::RShift)
				{
					game.setupOfGame ^= allSetings[i*4+j];
					sf::sleep(sf::microseconds(200000));
				}
			}
			
			
			lines.setSize(sf::Vector2f(5, 30));
			lines.setFillColor(sf::Color::White);
			lines.setPosition(122.5 +(x / 4 * j), 225 + (y / 2 * i));
			window.draw(lines);
			lines.setPosition(167.5 +(x / 4 * j), 225 + (y / 2 * i));
			window.draw(lines);
			lines.setSize(sf::Vector2f(15, 5));
			lines.setPosition(122.5 +(x / 4 * j), 225 + (y / 2 * i));
			window.draw(lines);
			lines.setPosition(157.5 +(x / 4 * j), 225 + (y / 2 * i));
			window.draw(lines);
			lines.setPosition(122.5 +(x / 4 * j), 250 + (y / 2 * i));
			window.draw(lines);
			lines.setPosition(157.5 +(x / 4 * j), 250 + (y / 2 * i));
			window.draw(lines);


			if(game.setupOfGame & allSetings[(i * 4) + j])
			{
				lines.setSize(sf::Vector2f(20, 20));
				lines.setPosition(137 +(x / 4 * j), 230 + (y / 2 * i));
				window.draw(lines);
			}
		}
	}
}

void HotKeys(ApplesGame::Game& game, sf::Event& event)
{
	if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F1)
	{
		game.setupOfGame ^= randnumberapple;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F2)
	{
		game.setupOfGame ^= infiniteapple;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F3)
	{
		game.setupOfGame ^= speedup;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F4)
	{
		game.setupOfGame ^= randnumberrock;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F5)
	{
		game.setupOfGame ^= rockoff;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F6)
	{
		game.setupOfGame ^= diagonalmovement;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F7)
	{
		game.setupOfGame ^= noborder;
		sf::sleep(sf::microseconds(150000));
	}
	else if((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::F8)
	{
		game.setupOfGame ^= havesound;
		sf::sleep(sf::microseconds(150000));
	}
}

void MoveCursor(bool (&selector)[2][4], sf::Event& event)
{
	for(size_t i = 0; i < 2; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{
			if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Up && selector[i][j] && i > 0)
			{
				selector[i][j] = false;
				selector[i-1][j] = true;
				sf::sleep(sf::microseconds(150000));
				break;
			} 
			else if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Down && selector[i][j] && i < 1)
			{
				selector[i][j] = false;
				selector[i+1][j] = true;
				sf::sleep(sf::microseconds(150000));
				break;
			} 
			else if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Left && selector[i][j] && j > 0)
			{
				selector[i][j] = false;
				selector[i][j-1] = true;
				sf::sleep(sf::microseconds(150000));
				break;
			} 
			else if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Right && selector[i][j] && j < 3)
			{
				selector[i][j] = false;
				selector[i][j+1] = true;
				sf::sleep(sf::microseconds(150000));
				break;
			} 
		}
	}
}

namespace ApplesGame
{
	const char* END_GAME_MESSAGE = "Press 'esc' to quit the game\nPress 'L' for continue\nPress 'H' to view information";
	const char* INFO_MESSAGE = "ON ARROW YOU ARE CAN CHANGE DIRECTION MOVEMENT:\n\tUP IT'S UP\n\tDOWN IT'S DOWN\n\tRIGHT IT'S RUGHT\n\tLEFT IT'S LEFT.\n\nAND YOU HAVE COMBITATION: \n\tUP+RIGHT OR UP+LEFT, \n\tDOWN+RIGHT OR DOWN+LEFT\n\nWHEN YOU ARE CRASH IN BORDER OR ROCK:\n\t\tYOU CAN RESTART GAME TO PRESS 'ENTER' \n\t\tOR CAN EXIT TO PRESS 'ESC'";
	const char* MENU_MESSAGE[] = {"hotkey F1\nRandom number of apple", "hotkey F2\nInfinite(apple) mode", "hotkey F3\nSpeed up after\n eaten apple", "hotkey F4\nRandom number of rocks", "hotkey F5\nDisable rocks", "hotkey F6\nPossibility diagonal movement", "hotkey F7\nBorder\n(don't work)", "hotkey F8\nSound"};
	// const char* HOTKEYS_MENU_MESSAGE[] = {"hotkey 1", "hotkey 2", "hotkey 3", "hotkey 4", "hotkey 5", "hotkey 6", "hotkey 7", "hotkey 8"};

	MenuInfo ShowInfo(sf::Font& font)
	{
		//Show Time
		sf::Text printTime;
		printTime.setFillColor(sf::Color::White);
		printTime.setCharacterSize(20);
		printTime.setPosition(10.f, 10.f);
		printTime.setFont(font);

		//Show Score
		sf::Text scoreShow;
		scoreShow.setFillColor(sf::Color::White);
		scoreShow.setCharacterSize(20);
		scoreShow.setPosition(10.f, 30.f);
		scoreShow.setFont(font);

		return { printTime, scoreShow };
	}

	void EndGame(sf::RenderWindow& window, sf::Font& font, sf::Event& event, bool& triggerEndGame, Game& game)
	{
		sf::SoundBuffer loseGame;
		loseGame.loadFromFile("Resources/Death.wav");
		sf::Sound sound;
		sound.setBuffer(loseGame);
		if(game.setupOfGame & havesound)
		{
			sound.play();
		}

		//Sort and view top's
		for(size_t i = 0; i < 6; i++)
		{
			if(game.scoresNames[i] == "Player")
			{
				game.scoresPoints[i] = game.numEatenApples;
			}
		}
		BubleSort(game);
		for (size_t i = 0; i < 6; i++)
		{
			DrawText(game.scoresNames[i], font, {100 + SCREEN_WIDTH / 10.f, 100 + (SCREEN_HEIGHT / 8.f) * i}, window);
			DrawText(std::to_string(game.scoresPoints[i]), font, {300 + SCREEN_WIDTH / 10.f, 100 + (SCREEN_HEIGHT / 8.f) * i}, window);
		}

		DrawText(END_GAME_MESSAGE, font, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, window);
		window.display();

		while (!triggerEndGame) {
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					triggerEndGame = true;
					window.close();
					break;
				}
			}
			if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Escape) {
				triggerEndGame = true;
				window.close();
				break;
			}
			else if (event.key.code == sf::Keyboard::L) {
				break;
			}
			else if (event.key.code == sf::Keyboard::H) {
				window.clear();	
				DrawText(INFO_MESSAGE, font, {10, 50}, window);
			}
		}
	}

	void GameSettingMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font, bool& triggerEndGame){
		bool stealConfiguring = true;
		bool selector [2][4] = {{true, false, false, false},
								{false, false, false, false}};
		while(stealConfiguring)
		{
			window.clear();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
					stealConfiguring = false;
					triggerEndGame = true;
					window.close();
					break;
				}
			}
			if (event.key.code == sf::Keyboard::Enter) {
				stealConfiguring = false;
				break;
			}

			HotKeys(game, event);
			DrawBorderMenu({SCREEN_WIDTH, SCREEN_HEIGHT}, window);
			for(size_t i = 0; i < 8; i++)
			{
				float x = 20 + ((SCREEN_WIDTH / 4) * (i % 4)), y = 30 + ((SCREEN_HEIGHT / 2) * (i / 4));
				DrawText(MENU_MESSAGE[i], font, {x, y}, window);
			}
			SelectionButtons(selector, {SCREEN_WIDTH, SCREEN_HEIGHT}, window, event, game);
			MoveCursor(selector, event);
			window.display();
		}
	}

	void WictoryMenu(Game& game, sf::Font& font, sf::RenderWindow& window, sf::Event& event)
	{
		if(game.numEatenApples == NUM_APPLE - game.RandomNumForApple){
			game.wictory = true;
		}

		if(game.wictory)
		{
			sf::Text wictoryText; 
			wictoryText.setFont(font);
			wictoryText.setCharacterSize(20);
			wictoryText.setFillColor(sf::Color::Green);
			wictoryText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
			wictoryText.setString("Winner!!!\n\"Enter\" for continue\n\"Esc\" for close game");
			window.draw(wictoryText);
			window.display();
		}
		while(game.wictory)
		{
			while (window.pollEvent(event))
			{
				if (((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed) {
					game.wictory = false;
					window.close();
					break;
				}
			}
			if(event.key.code == sf::Keyboard::Enter)
			{
				break;
			}

			sf::sleep(sf::microseconds(100000));
		}
	}
}