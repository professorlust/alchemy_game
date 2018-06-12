#ifndef REACTION_HPP
#define REACTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.hpp"
#include "Reagent.hpp"

class Reaction
{
private:
	std::vector<unsigned int> input_reagents;
	std::vector<Reagent> output_reagents;

	sf::String description = "";

public:
	Reaction(std::vector<unsigned int> input, std::vector<unsigned int> output, bool is_sorted = true);
	Reaction(std::vector<unsigned int> input, std::vector<Reagent> output, bool is_sorted = true);
	Reaction(const Reaction &copy);
	~Reaction();

	/* Methods for setting data */
	void set_description(sf::String description_);

	/* Methods for obtaining data. All methods are CONST */
	bool check_reaction(std::vector<unsigned int> input, bool is_sorted) const; // Validation reaction by Item IDs. Faster
	bool check_reaction(std::vector<Item> input, bool is_sorted) const; // Validation reaction by objects of Item class. Slower
	std::vector<Reagent> get_output_items() const;
	std::vector<unsigned int> get_input_items() const;
};
#endif