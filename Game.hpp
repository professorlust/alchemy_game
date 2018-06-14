#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Reaction.hpp"
#include "Item.hpp"

class Game
{
protected:
	sf::String name = "not initialized"; // Name of the game
	sf::String author;
	sf::String description; // Information about the game

	/* Game settings */
	bool top_element_panel_ = true;
	bool deletion_elements_RMB_ = true;

public:
	Game();
	~Game();

	/* General methods */
	// games. See standart_games folder
	void charodey(std::vector <sf::Texture> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy);

	/* Methods for obtaining data. All methods are CONST */
	sf::String get_game_name() const;

	// settings
	bool deletion_elements_RMB() const;
	bool render_top_elements_panel() const;

	// Methods for obtaining game information
	void console_show_information() const;
	void file_show_full_information() const;
};
#endif