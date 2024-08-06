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
	bool triggerEndGame = false; //Check Pressed Esc After Collision
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

	//Main Cycle Of Game
	while (window.isOpen() && !triggerEndGame) {
		int frameCounter = 0;
		
		// Initialize 
		sf::Event event;
		float Time = 0.f;
		int bufferEaten = 0;
		bool rockCollision = false; // Collision with rocks
		bool borderCollision = false;
		ApplesGame::GameSettingMenu(game, event, window, font, triggerEndGame); // Menu for setting game
		
		// Set Game
		ApplesGame::InitGame(game);
		ApplesGame::MenuInfo info = ApplesGame::ShowInfo(font);

		// Time
		sf::Clock gameClock;
		float lastTime = gameClock.getElapsedTime().asSeconds(); //Time
		
		while (window.isOpen() && !triggerEndGame && !rockCollision && !game.wictory)
		{
			if ((game.setupOfGame & havesound) && game.numEatenApples != bufferEaten) {
				goodSound.play();
				bufferEaten = game.numEatenApples;
			}

			sf::sleep(sf::microseconds(16));

			//Time
			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			frameCounter++;

			//Game Time
			Time += deltaTime;
			info.time.setString("Frame: " + std::to_string(frameCounter) + "\t Time: " + std::to_string(Time));

			//Check event
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
			
			//Game move & direction
			SetDirection(game, event);
			SetMovementInDirection(game, deltaTime);
			
			//Check all collision
			CheckCollision(rockCollision, game, window, font, event, triggerEndGame, borderCollision);
		 
			if (rockCollision || borderCollision)break;

			//Time Output Template
			info.score.setString("Score of eaten applles: " + std::to_string(game.numEatenApples));
			
			//Prepare Window
			DrawGame(window, game, info);

			if(!(game.setupOfGame & infiniteapple) && game.numEatenApples == NUM_APPLE - game.RandomNumForApple){
				game.wictory = true;
				WictoryMenu(game, font, window, event);
			}
		}
	}
	return 0;
}
