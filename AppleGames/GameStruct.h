#pragma once
#include "InitRock.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	const enum class PlayerDirection : int
	{
		Up = 0,
		Right = 1,
		Down = 2,
		Left = 3,
		RigthDown = 4,
		LeftDown = 5,
		RightUp = 6,
		LeftUp = 7,
	};

	const enum class GameState : int
	{
		MainMenu = 0,
		Play = 1,
		SettingMenu = 2,
		ScoreAndLegend = 3,
		PauseMenu = 4,
		GameOver = 5,
		Exit = 6,
	};

	struct Player
	{
		Position2D position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
		sf::Texture playerTexture;
	};

	struct Game
	{
		Player player;
		GameState gameState = GameState::MainMenu;
		bool lastStatePause = false;
		int frameCounter = 0;

		//Apples data
		Position2D applesPositions[NUM_APPLE];
		sf::Sprite applesSprite[NUM_APPLE];
		sf::Texture appleTexture;

		//Rock data
		Position2D rocksPositions[NUM_ROCK];
		sf::Sprite rockSprite[NUM_ROCK];
		sf::Texture rockTexture;
		SizeRockShape sizeRockShape[NUM_ROCK];

		//Game mode
		unsigned char setupOfGame = 0x00;

		//Scores
		int numEatenApples = 0;
		int bestValueEatenApple = 0;
		int bufferEaten = 0;
		sf::RectangleShape background;
		int RandomNumForApple = 0;
		int RandomNumForRock = 0;
		int scoresPoints[6] = {0, 0, 0, 0, 0, 0};
		std::string scoresNames[6] = {"Nagibator777", "Guest", "Nobody", "***DENCHIK***", "Phedot", "Player"};

		//Time
		float Time = 0.f;
		sf::Clock gameClock;
		float lastTime = gameClock.getElapsedTime().asSeconds();
		float currentTime = gameClock.getElapsedTime().asSeconds();
	};

	void InitGame(Game& game);

	void InitPlayer(Player& player);

	void BubleSort(Game& game);
}