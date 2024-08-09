#include "Menu.h"
#include "Constants.h"
#include "GameStruct.h"
#include "Math.h"
#include <SFML/Audio.hpp>
#include <sys/_types/_size_t.h>
#include <cstdint>

void DrawText(sf::String text, sf::Font& font, ApplesGame::Vector2D coordinateOfWindow, sf::RenderWindow& window, sf::Color color = sf::Color::White)
{
	sf::Text item;
	item.setFont(font);
	item.setCharacterSize(20);
	item.setFillColor(color);
	item.setPosition(coordinateOfWindow.x, coordinateOfWindow.y);
	item.setString(text);
	window.draw(item);
}

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

				if(event.key.code == sf::Keyboard::Enter)
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
	const char* END_GAME_MESSAGE = "Press 'esc' to quit to the main menu\nPress 'L' for continue\nPress 'H' to view information";
	const char* INFO_MESSAGE = "ON ARROW YOU ARE CAN CHANGE DIRECTION MOVEMENT:\n\tUP IT'S UP\n\tDOWN IT'S DOWN\n\tRIGHT IT'S RUGHT\n\tLEFT IT'S LEFT.\n\nAND YOU HAVE COMBITATION: \n\tUP+RIGHT OR UP+LEFT, \n\tDOWN+RIGHT OR DOWN+LEFT\n\nWHEN YOU ARE CRASH IN BORDER OR ROCK:\n\t\tYOU CAN RESTART GAME TO PRESS 'L' \n\t\tOR CAN GO TO MAIN WHEN PRESS 'ESC'";
	const char* MENU_MESSAGE[] = {"hotkey F1\nRandom number of apple", "hotkey F2\nInfinite(apple) mode", "hotkey F3\nSpeed up after\n eaten apple", "hotkey F4\nRandom number of rocks", "hotkey F5\nDisable rocks", "hotkey F6\nPossibility diagonal movement", "hotkey F7\nBorder\n(don't work)", "hotkey F8\nSound"};
	
	void DrawTop(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font)
	{
		window.clear();

		for(size_t i = 0; i < 6; i++)
		{
			if(game.scoresNames[i] == "Player")
			{
				game.scoresPoints[i] = game.bestValueEatenApple;
			}
		}

		BubleSort(game);
		DrawText("TOP:", font, {100 + SCREEN_WIDTH / 2.f, 50}, window, sf::Color::Red);
		for (size_t i = 0; i < 6; i++)
		{
			DrawText(game.scoresNames[i], font, 
				{100 + SCREEN_WIDTH / 2.f, 100 + (SCREEN_HEIGHT / 8.f) * i}, window);
			DrawText(std::to_string(game.scoresPoints[i]), font, 
				{300 + SCREEN_WIDTH / 2.f, 100 + (SCREEN_HEIGHT / 8.f) * i}, window);
		}
		DrawText(INFO_MESSAGE, font, {10, 50}, window);

		window.display();

		while(game.gameState == GameState::ScoreAndLegend)
		{
			while(window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}				
			}

			if (event.key.code == sf::Keyboard::Escape) 
			{
				game.gameState = GameState::MainMenu;
				sf::sleep(sf::microseconds(150000));
				break;
			}
		}
	}

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

	void EndGame(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font)
	{
		sf::SoundBuffer loseGame;
		loseGame.loadFromFile("Resources/Death.wav");
		sf::Sound sound;
		sound.setBuffer(loseGame);
		if(game.setupOfGame & havesound)
		{
			sound.play();
		}
		DrawText(END_GAME_MESSAGE, font, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, window);
		window.display();
		while (game.gameState == GameState::GameOver) 
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}
			}

			if(event.key.code == sf::Keyboard::Escape)
			{
				game.gameState = GameState::MainMenu;
			}
			else if (event.key.code == sf::Keyboard::L) 
			{
				game.gameState = GameState::Play;
				break;
			}
			else if (event.key.code == sf::Keyboard::H) 
			{
				window.clear();	
				DrawText(INFO_MESSAGE, font, {10, 50}, window);
				window.display();
			}
		}
	}

	void MainMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font)
	{
		bool selector[] = {true, false, false, false};
		while(game.gameState == GameState::MainMenu)
		{
			window.clear();

			while(window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}				
			}

			for(size_t i = 0; i < 4; i++)
			{
				if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Up && !selector[0]) 
				{
					if(selector[i])
					{
						selector[i] = false;
						selector[i-1] = true;
						sf::sleep(sf::microseconds(150000));
						break;
					}
				}
				else if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Down && !selector[3]) 
				{
					if(selector[i])
					{
						selector[i] = false;
						selector[i+1] = true;
						sf::sleep(sf::microseconds(150000));
						break;
					}
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (selector[0])
					{
						game.gameState = GameState::Play;
					}
					else if (selector[1])
					{
						game.gameState = GameState::ScoreAndLegend;
					}
					else if (selector[2])
					{
						game.gameState = GameState::SettingMenu;
					}
					else if (selector[3])
					{
						game.gameState = GameState::Exit;
					}
				}
			}

			DrawText("Play", font, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4}, window, selector[0] ? sf::Color::Red : sf::Color::White);
			DrawText("Top scores & Legend", font, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 30}, window, selector[1] ? sf::Color::Red : sf::Color::White);
			DrawText("Settings", font, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 60}, window, selector[2] ? sf::Color::Red : sf::Color::White);
			DrawText("Exit", font, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 90}, window, selector[3] ? sf::Color::Red : sf::Color::White);
			window.display();
		}
	}

	void GameSettingMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font){
		bool selector [2][4] = {{true, false, false, false},
								{false, false, false, false}};
		while(game.gameState == GameState::SettingMenu)
		{
			sf::sleep(sf::microseconds(16));
			window.clear();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}
			}
			if (event.key.code == sf::Keyboard::Escape) 
			{
				game.gameState = GameState::MainMenu;
				sf::sleep(sf::microseconds(150000));
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

	void PauseMenu(Game& game, sf::Event& event, sf::RenderWindow& window, sf::Font& font)
	{
		DrawText("Press 'Enter' for continue", font, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, window, sf::Color::Green);
		DrawText("Press 'Esc' go Main Menu", font, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 30}, window, sf::Color::Red);
		window.display();
		while(game.gameState == GameState::PauseMenu)
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}
			}

			if(event.key.code == sf::Keyboard::Enter)
			{	
				game.gameState = GameState::Play;
				sf::sleep(sf::microseconds(150000));
				break;
			}

			if(event.key.code == sf::Keyboard::Escape)
			{
				game.gameState = GameState::MainMenu;
				sf::sleep(sf::microseconds(150000));
				break;
			}
		}
	}

	void WictoryMenu(Game& game, sf::Font& font, sf::RenderWindow& window, sf::Event& event)
	{
		DrawText("Winner!!!\n\"Enter\" for continue\n\"Esc\" go to Main Menu", 
			font, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, window, sf::Color::Green);
		window.display();

		while(game.gameState == GameState::GameOver)
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
				{
					game.gameState = GameState::Exit;
					window.close();
					break;
				}
			}
			
			if(event.key.code == sf::Keyboard::Enter)
			{
				game.gameState = GameState::Play;
				sf::sleep(sf::microseconds(150000));
				break;
			}
			else if(event.key.code == sf::Keyboard::Escape)
			{
				game.gameState = GameState::MainMenu;
				sf::sleep(sf::microseconds(150000));
				break;
			}

		}
	}
}