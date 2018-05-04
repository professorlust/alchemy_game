#ifndef MAIN_HPP
#define MAIN_HPP

#include "Element.hpp"
#include "Reaction.hpp"
#include "standart_games\standart_games.hpp"

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