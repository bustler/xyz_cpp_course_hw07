#pragma once
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct SizeRockShape
	{
		float width = GetRandomSizeForRocks(MIN_ROCK_SIZE, MAX_ROCK_SIZE);
		float height = GetRandomSizeForRocks(MIN_ROCK_SIZE, MAX_ROCK_SIZE);
	};

	float GetRandomSizeForRocks(float minRockSize, float maxRockSize);
}