#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Reaction.hpp"
#include "Element.hpp"

#ifndef GAME_HPP
#define GAME_HPP
class Game
{
protected:
	std::vector<sf::Texture*> textures;
	std::vector<Element> element_list;
	std::vector<Reaction> reactions_list;
	std::vector<unsigned int> started_elements;

	unsigned int number_of_elements;
	unsigned int number_of_reactions;

	sf::String name;
	sf::String author; // Author's name
	sf::String description; // Information about the game

	virtual void initialization_textures() = 0;
	virtual void initialization_elements() = 0;
	virtual void initialization_reactions() = 0;
	virtual void initialization_started_elements() = 0;

public:
	void load_game(std::vector<Element*> &global_element_list, std::vector<Reaction*> &global_reactions_list, std::vector<unsigned int> &global_started_elements);
	void console_show_information();
	void file_show_full_information();
	
	unsigned int get_number_of_elements();
	unsigned int get_number_of_reactions();

	Game();
	~Game();
};
#endif