#ifndef SAVE_AND_LOAD
#define SAVE_AND_LOAD

#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"

void save_game(std::vector<Item*> items_list, std::vector<Item*> items_on_map, std::string file_name = "game_save");
bool load_save_game(std::vector<Item*> &items_list, std::vector<Item*> &items_on_map, std::string file_name);
#endif