#ifndef LOAD_GAME_DATA_FROM_FILE_HPP
#define LOAD_GAME_DATA_FROM_FILE_HPP

#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Reaction.hpp"
#include "Item_color.hpp"

bool load_game_data_from_file(std::vector<Item*> &items_list_copy, std::vector<Reaction*> &reactions_list_copy, std::vector<unsigned int> &started_items_copy, std::string file_name);
#endif