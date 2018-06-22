#ifndef REAGENT_HPP
#define REAGENT_HPP

#include <vector>

struct Reagent
{
	unsigned int id = 0;
	bool remove = false;

	uint16_t chance = 10000;

	std::vector<unsigned int> found_on_map;
	std::vector<unsigned int> not_found_on_map;
};
#endif