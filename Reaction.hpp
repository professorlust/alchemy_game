#ifndef REACTION_HPP
#define REACTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.hpp"

class Reaction
{
private:
	std::vector<unsigned int> input_reagents;
	std::vector<unsigned int> output_reagents;

	sf::String description = "";

public:
	Reaction(std::vector<unsigned int> input_reagents, std::vector<unsigned int> output_reagents, bool is_sorted = true);
	Reaction(const Reaction &reaction);
	~Reaction();

	/* Methods for setting data */
	void set_description(sf::String description);

	/* Methods for obtaining data. All methods are CONST */
	bool check_reaction(std::vector<unsigned int> input_reagents, bool is_sorted) const; // Validation reaction by Item IDs. Faster
	bool check_reaction(std::vector<Item*> input_reagents, bool is_sorted) const; // Validation reaction by objects of Item class. Slower
	std::vector<unsigned int> get_output_items() const;
	std::vector<unsigned int> get_input_items() const;
};
#endif