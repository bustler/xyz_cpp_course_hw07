#include "Player.h"
#include "Constants.h"
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	void SetDirection(Game& game, sf::Event& event) {
		//Set Direction
		if ((game.setupOfGame & diagonalmovement) && event.key.code == sf::Keyboard::Down 
				&& event.key.code == sf::Keyboard::Right) 
		{
			game.player.direction = PlayerDirection::RigthDown;// Right & Down
			game.player.sprite.setRotation(45.f);
		}
		else if ((game.setupOfGame & diagonalmovement) && event.key.code == sf::Keyboard::Down 
				&& event.key.code == sf::Keyboard::Left) 
		{
			game.player.direction = PlayerDirection::LeftDown;// Left & Down
			game.player.sprite.setRotation(135.f);
		}
		else if ((game.setupOfGame & diagonalmovement) && event.key.code == sf::Keyboard::Up 
				&& event.key.code == sf::Keyboard::Right) 
		{
			game.player.direction = PlayerDirection::RightUp;// Right & up
			game.player.sprite.setRotation(315.f);
		}
		else if ((game.setupOfGame & diagonalmovement) && event.key.code == sf::Keyboard::Up 
				&& event.key.code == sf::Keyboard::Left) 
		{
			game.player.direction = PlayerDirection::LeftUp;// left & up
			game.player.sprite.setRotation(225.f);
		}
		else if (event.key.code == sf::Keyboard::Right) 
		{
			game.player.direction = PlayerDirection::Right;// right
			game.player.sprite.setRotation(0.f);
		}
		else if (event.key.code == sf::Keyboard::Up) 
		{
			game.player.direction = PlayerDirection::Up;// Up
			game.player.sprite.setRotation(270.f);
		}
		else if (event.key.code == sf::Keyboard::Left) 
		{
			game.player.direction = PlayerDirection::Left;// left
			game.player.sprite.setRotation(180.f);
		}
		else if (event.key.code == sf::Keyboard::Down) 
		{
			game.player.direction = PlayerDirection::Down; // down
			game.player.sprite.setRotation(90.f);
		}
	}

	void SetMovementInDirection(Game& game, float& deltaTime)
	{
		//Movement In Direction
		switch (game.player.direction) {
		case PlayerDirection::Up:
			game.player.position.y -= game.player.speed * deltaTime;
			break;
		case PlayerDirection::Right:
			game.player.position.x += game.player.speed * deltaTime;
			break;
		case PlayerDirection::Down:
			game.player.position.y += game.player.speed * deltaTime;
			break;
		case PlayerDirection::Left:
			game.player.position.x -= game.player.speed * deltaTime;
			break;
		case PlayerDirection::RigthDown:
			game.player.position.y += game.player.speed * ANGLE_MOVEMENT * deltaTime;
			game.player.position.x += game.player.speed * ANGLE_MOVEMENT * deltaTime;
			break;
		case PlayerDirection::RightUp:
			game.player.position.y -= game.player.speed * ANGLE_MOVEMENT * deltaTime;
			game.player.position.x += game.player.speed * ANGLE_MOVEMENT * deltaTime;
			break;
		case PlayerDirection::LeftDown:
			game.player.position.y += game.player.speed * ANGLE_MOVEMENT * deltaTime;
			game.player.position.x -= game.player.speed * ANGLE_MOVEMENT * deltaTime;
			break;
		case PlayerDirection::LeftUp:
			game.player.position.y -= game.player.speed * ANGLE_MOVEMENT * deltaTime;
			game.player.position.x -= game.player.speed * ANGLE_MOVEMENT * deltaTime;
			break;
		}
	}

	void CheckCollision(Game& game, sf::RenderWindow& window, sf::Font& font, sf::Event& event) {
		//Check Rock Collision With PLayer
		if(!(game.setupOfGame & rockoff))
		{
			for (int i = 0; i < NUM_ROCK - game.RandomNumForRock 
					&& !(game.gameState == ApplesGame::GameState::Exit); i++) {
				if (fabs(game.rocksPositions[i].x - game.player.position.x) < (PLAYER_SIZE + game.sizeRockShape[i].width) / 2.f 
					&& fabs(game.rocksPositions[i].y - game.player.position.y) < (PLAYER_SIZE + game.sizeRockShape[i].height) / 2.f)
				{
					game.gameState = GameState::GameOver;
				}
			}
		}

		//Check Border Collision With PLayer
		if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f 
			|| game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH
			|| game.player.position.y - PLAYER_SIZE / 2.f < 0.f 
			|| game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			game.gameState = GameState::GameOver;
		}
		
		//Check Apple Collision With PLayer
		for (int i = 0; i < NUM_APPLE - game.RandomNumForApple; i++) {
			float dx = (float)fabs(game.player.position.x - game.applesPositions[i].x);
			float dy = fabs(game.player.position.y - game.applesPositions[i].y);
			float deltaDistance = sqrt((dx * dx) + (dy * dy));
			if (deltaDistance <= (APPLE_SIZE + PLAYER_SIZE) / 2.f) {
				if((game.setupOfGame & infiniteapple))
				{
					game.applesPositions[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					game.applesSprite[i].setPosition(game.applesPositions[i].x, game.applesPositions[i].y);
				} 
				else if(game.numEatenApples < NUM_APPLE - game.RandomNumForApple)
				{
					game.applesPositions[i] = {-50,-50};
					game.applesSprite[i].setPosition(game.applesPositions[i].x, game.applesPositions[i].y);
				} 

				game.numEatenApples++;
				
				if((game.setupOfGame & speedup))
				{
					game.player.speed += ACCELERATION;
				}
			}
		}
	}
}