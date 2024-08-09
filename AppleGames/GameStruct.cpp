#include "GameStruct.h"
#include "Constants.h"
#include <SFML/Audio.hpp>


namespace ApplesGame
{
	void InitPlayer(Player& player)
	{
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;
		player.sprite.setRotation(0.f);

		player.playerTexture.loadFromFile("Resources/Player.png");
		player.sprite.setTexture(player.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5, 0.5);
	}

	void InitGame(Game& game) {
		// Player player;
		InitPlayer(game.player);
		game.numEatenApples = 0;
		
		// Modes with random
		if(game.setupOfGame & randnumberapple) // apples
		{
			game.RandomNumForApple = RandomNumber();
		}
		if(game.setupOfGame & randnumberrock) // rocks
		{
			game.RandomNumForRock = RandomNumber();
		}

		game.appleTexture.loadFromFile("Resources/Apple.png");
		game.rockTexture.loadFromFile("Resources/Rock.png");
		// Init apples
		for (int i = 0; i < NUM_APPLE - game.RandomNumForApple; i++)
		{
			game.applesPositions[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

			game.applesSprite[i].setTexture(game.appleTexture);
			SetSpriteSize(game.applesSprite[i], APPLE_SIZE, APPLE_SIZE);
			SetSpriteRelativeOrigin(game.applesSprite[i], 0.5, 0.5);
			game.applesSprite[i].setPosition(game.applesPositions[i].x, game.applesPositions[i].y);
		}

		// Init rocks
		if(!(game.setupOfGame & rockoff)){
			for (int i = 0; i < NUM_ROCK - game.RandomNumForRock; i++)
			{
				game.rocksPositions[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

				game.rockSprite[i].setTexture(game.rockTexture);
				SetSpriteSize(game.rockSprite[i], game.sizeRockShape[i].width, game.sizeRockShape[i].height);
				SetSpriteRelativeOrigin(game.rockSprite[i], 0.5, 0.5);
				game.rockSprite[i].setPosition(game.rocksPositions[i].x, game.rocksPositions[i].y);
			}
		}
	}

	//Sort Top Player
	void BubleSort(Game& game)
	{
		bool sortTrigger = false;
		do
		{
			sortTrigger = false;
			for(size_t i = 0; i < 5; i++)
			{
				if(game.scoresPoints[i] < game.scoresPoints[i+1])
				{
					sortTrigger = true;
					int tempScore = game.scoresPoints[i];
					std::string tempName = game.scoresNames[i];

					game.scoresPoints[i] = game.scoresPoints[i+1];
					game.scoresNames[i] = game.scoresNames[i+1];
					game.scoresPoints[i+1] = tempScore;
					game.scoresNames[i+1] = tempName;
				}
			}
		} while(sortTrigger);
	}
}