#pragma once
#include <cstdlib>

namespace sf {
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x;
		float y;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

	float GetRandomSizeForRocks(float minRockSize, float maxRockSize);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	int RandomNumber(int n = 16);
}