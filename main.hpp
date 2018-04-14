#include "Element.hpp"
#include "Reaction.hpp"
#include "standart_games\standart_games.hpp"

#ifndef MAIN_HPP
#define MAIN_HPP
void add_to_erase_list(Element *element, std::vector<unsigned int> *erase_vector, unsigned int num)
{
	if (!element->is_static()) 
	{
		erase_vector->push_back(num);
	}
}

bool spawn_element(Element *element, std::vector<Element*> *elements_on_map_vector, sf::Vector2f spawn_position)
{
	Element::set_opened(*element);
	if (!element->is_static()) 
	{
		elements_on_map_vector->push_back(new Element(*element, spawn_position));
		return true;
	}
	else 
	{
		return false;
	}
}

bool spawn_static_element(Element *element, std::vector<Element*> *elements_on_map_vector, sf::Vector2f spawn_position)
{
	Element::set_opened(*element);
	if (element->is_static()) 
	{
		elements_on_map_vector->push_back(new Element(*element, spawn_position));
		return true;
	}
	else 
	{
		return false;
	}
}

std::string update_opened_elements_string(int opened, int all)
{
	return 
	"Open elements: " + 
	std::to_string(opened) + 
	" / " + 
	std::to_string(all);
}

std::string update_page_string(int page, int all)
{
	return 
	"Page: " + 
	std::to_string(page + 1) + 
	" / " + 
	std::to_string(all + 1);
}
#endif