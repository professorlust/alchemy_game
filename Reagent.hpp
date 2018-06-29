#ifndef REAGENT_HPP
#define REAGENT_HPP

#include <vector>
#include <random>
#include "Item.hpp"

struct Reagent
{
	unsigned int id = 0;
	bool remove = false;

	uint16_t chance = 10000;

	std::vector<unsigned int> found_on_map;
	std::vector<unsigned int> not_found_on_map;
	std::vector<unsigned int> items_is_open;
	std::vector<unsigned int> items_is_not_open;

	bool check_conditions(const std::vector<Item> items_list, const std::vector<Item> items_on_map, unsigned int last_item);
};
#endif