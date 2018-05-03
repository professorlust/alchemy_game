#ifndef REACTION_HPP
#define REACTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Element.hpp"

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
	bool check_reaction(std::vector<unsigned int> input_reagents, bool is_sorted); // Validation reaction by Item IDs. Faster
	bool check_reaction(std::vector<Element*> input_reagents, bool is_sorted); // Validation reaction by objects of Element class. Slower
	void set_description(sf::String description);
	std::vector<unsigned int> get_output_items();
};
#endif