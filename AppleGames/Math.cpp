#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight) {
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY){
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	int RandomNumber(int n)
	{
		int x = std::rand() % n;
		return x;
	}
}