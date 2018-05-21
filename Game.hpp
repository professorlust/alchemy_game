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
	std::vector<sf::Texture*> textures;
	std::vector<Item> element_list;
	std::vector<Reaction> reactions_list;
	std::vector<unsigned int> started_items;

	unsigned int number_of_items;
	unsigned int number_of_reactions;

	sf::String name; // Name of the game
	sf::String author; // Author's name
	sf::String description; // Information about the game

	virtual void initialization_textures() = 0;
	virtual void initialization_items() = 0;
	virtual void initialization_reactions() = 0;
	virtual void initialization_started_items() = 0;

public:
	Game();
	~Game();

	void load_game(std::vector<Item*> &items_list_copy, std::vector<Reaction*> &reactions_list_copy, std::vector<unsigned int> &started_items_copy);
	void open_all_items(std::vector<Item*> &items);

	/* Methods for obtaining data. All methods are CONST */
	unsigned int get_number_of_items() const;
	unsigned int get_number_of_reactions() const;
	void console_show_information() const;
	void file_show_full_information() const;
	sf::String get_game_name() const;
};
#endif