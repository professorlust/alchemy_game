#ifndef GAME_SETTINGS
#define GAME_SETTINGS

#include "Config.hpp"

struct Game_settings
{
	sf::String name = "not initialized";
	sf::String author;
	sf::String description; // Information about the game

	/* Game settings */
	bool render_top_elements_panel = true;
	bool deletion_elements_RMB = true;
};
#endif