#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Draw.h"

namespace ApplesGame
{
	void DrawGame(sf::RenderWindow& window, Game& game, MenuInfo& info)
	{
		window.clear();
		if(!(game.setupOfGame & rockoff))
		{
			for (size_t i = 0; i < NUM_ROCK - game.RandomNumForRock; i++) {
				window.draw(game.rockSprite[i]);
			}
		}
		for (size_t i = 0; i < NUM_APPLE - game.RandomNumForApple; i++) {
			window.draw(game.applesSprite[i]);
		}

		game.player.sprite.setPosition(game.player.position.x, game.player.position.y);
		window.draw(game.player.sprite);
		window.draw(info.time);
		window.draw(info.score);
		window.display();
	}
}