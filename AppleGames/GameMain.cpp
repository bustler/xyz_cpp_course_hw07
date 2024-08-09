#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Menu.h"
#include "Draw.h"
#include "GameStruct.h"
#include "Player.h"

int main()
{
	ApplesGame::Game game;

	//Init Random Number
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apple games!"); //Header
	sf::Font font; font.loadFromFile("Resources/Fonts/Roboto-Regular.ttf"); //Set Font
	
	sf::SoundBuffer appleEatenSound;
	appleEatenSound.loadFromFile("Resources/AppleEat.wav");
	sf::Sound goodSound;
	goodSound.setBuffer(appleEatenSound);

	//Create random score
	for(size_t i = 0; i < 5; i++)
	{
		game.scoresPoints[i] = ApplesGame::RandomNumber(50);
	}

	ApplesGame::MenuInfo info = ApplesGame::ShowInfo(font);
	//Main Cycle Of Game
	while (window.isOpen() && !(game.gameState == ApplesGame::GameState::Exit)) {
		sf::Event event;
		
		if (!game.lastStatePause)
		{
			game.frameCounter = 0;
			
			// Initialize 
			game.Time = 0.f;
			game.bufferEaten = 0;
			
			// Set Game
			ApplesGame::InitGame(game);
		} 
		else
		{
			game.lastStatePause = false;
		}

		if (window.isOpen() && game.gameState == ApplesGame::GameState::MainMenu)
		{
			ApplesGame::MainMenu(game, event, window, font);
		}

		if (window.isOpen() && game.gameState == ApplesGame::GameState::SettingMenu)
		{
			ApplesGame::GameSettingMenu(game, event, window, font);
		}

		if (window.isOpen() && game.gameState == ApplesGame::GameState::PauseMenu)
		{
			ApplesGame::PauseMenu(game, event, window, font);
		}

		if (window.isOpen() && game.gameState == ApplesGame::GameState::ScoreAndLegend)
		{
			ApplesGame::DrawTop(game, event, window, font);
		}

		if (window.isOpen() && game.gameState == ApplesGame::GameState::GameOver)
		{
			ApplesGame::EndGame(game, event, window, font);
		}

		game.currentTime = game.gameClock.getElapsedTime().asSeconds();
		game.lastTime = game.currentTime;
		while (window.isOpen() && game.gameState == ApplesGame::GameState::Play)
		{
			if ((game.setupOfGame & havesound) && game.numEatenApples != game.bufferEaten) {
				goodSound.play();
				game.bufferEaten = game.numEatenApples;
			}

			sf::sleep(sf::microseconds(16)); 

			//Time
			game.currentTime = game.gameClock.getElapsedTime().asSeconds();
			float deltaTime = game.currentTime - game.lastTime;
			game.lastTime = game.currentTime;
			game.frameCounter++;

			//Game Time
			game.Time += deltaTime;
			info.time.setString("Frame: " + std::to_string(game.frameCounter) + "\t Time: " + std::to_string(game.Time));

			//Check event
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			if (event.key.code == sf::Keyboard::Space)
			{
				game.gameState = ApplesGame::GameState::PauseMenu;
				game.lastStatePause = true;
			} 
			
			//Game move & direction
			SetDirection(game, event);
			SetMovementInDirection(game, deltaTime);
			
			//Check all collision
			CheckCollision(game, window, font, event);

			//Time Output Template
			info.score.setString("Score of eaten applles: " + std::to_string(game.numEatenApples));
			if (game.bestValueEatenApple < game.numEatenApples)
			{
				game.bestValueEatenApple = game.numEatenApples;
			}
			
			//Prepare Window
			DrawGame(window, game, info);

			if(!(game.setupOfGame & infiniteapple) 
					&& (game.numEatenApples == NUM_APPLE - game.RandomNumForApple))
			{
				game.gameState = ApplesGame::GameState::GameOver;
				WictoryMenu(game, font, window, event);
			}
		}
	}
	return 0;
}
