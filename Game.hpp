#ifndef GAME_HPP
#define GAME_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Reaction.hpp"
#include "Element.hpp"

class Game
{
protected:
	std::vector<sf::Texture*> textures;
	std::vector<Element> element_list;
	std::vector<Reaction> reactions_list;
	std::vector<unsigned int> started_elements;

	unsigned int number_of_elements;
	unsigned int number_of_reactions;

	sf::String name; // Name of the game
	sf::String author; // Author's name
	sf::String description; // Information about the game

	virtual void initialization_textures() = 0;
	virtual void initialization_elements() = 0;
	virtual void initialization_reactions() = 0;
	virtual void initialization_started_elements() = 0;

public:
	Game();
	~Game();

	void load_game(std::vector<Element*> &global_element_list, std::vector<Reaction*> &global_reactions_list, std::vector<unsigned int> &global_started_elements);
	void open_all_items(std::vector<Element*> &items);

	/* Methods for obtaining data. All methods are CONST */	
	unsigned int get_number_of_elements() const;
	unsigned int get_number_of_reactions() const;
	void console_show_information() const;
	void file_show_full_information() const;

	static void save_game(std::vector<Element*> items_list, std::vector<Element*> items_on_map) const;
	static void load_game();
};
#endif