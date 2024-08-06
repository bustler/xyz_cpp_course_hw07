#include "InitRock.h"

namespace ApplesGame
{
	float GetRandomSizeForRocks(float minRockSize, float maxRockSize)
	{
		return rand() / (float)RAND_MAX * (maxRockSize - minRockSize) + minRockSize;
	}
}