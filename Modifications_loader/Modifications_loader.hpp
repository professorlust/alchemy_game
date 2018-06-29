#ifndef MODIFICATIONS_LOADER
#define MODIFICATIONS_LOADER

#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

#include "../Game_settings.hpp"
#include "../Item.hpp"
#include "../Reaction.hpp"
#include "../Reagent.hpp"
#include "../Item_color.hpp"
#include "../Config.hpp"

// = = = = = = = = = = = = = = = =
		 /* T E S T I N G ! ! ! */
// = = = = = = = = = = = = = = = =

namespace Modifications_loader
{
	/* General processing methods */
	void load_modification(std::string file_name, std::vector <sf::Texture*> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy, Game_settings &game_settings);
	void modification_information_file(const std::vector<Item> &items_list, const std::vector<Reaction> &reactions_list, const std::vector<Reagent> &started_items, const Game_settings &game_settings);

	/* Methods for creating modifications players */
	void create_modification_template();
	void remove_spaces(std::wstring &string, bool remove_quotes = false);
	unsigned int get_item_id_by_name(std::wstring name, const std::vector<Item> &items_list_copy);
	sf::String get_item_name_by_id(unsigned int id, const std::vector<Item> &items_list_copy);
}
#endif