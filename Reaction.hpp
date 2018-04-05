#ifndef REACTION_HPP
#define REACTION_HPP

#include "Item.hpp"
#include <vector>

class Reaction
{
private:
	std::vector<unsigned int> output_reagents;
	std::vector<unsigned int> input_reagents;
	sf::String description;

public:
	Reaction(std::vector<unsigned int> input_reagents, std::vector<unsigned int> output_reagents, bool is_sorted = true);
	~Reaction();
	
	bool check_reaction(std::vector<unsigned int> input_reagents, bool is_sorted = true);
	std::vector<unsigned int> get_output_reagents();
	std::vector<unsigned int> get_input_reagents();
};

#endif