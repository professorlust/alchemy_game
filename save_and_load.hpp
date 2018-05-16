#ifndef SAVE_AND_LOAD
#define SAVE_AND_LOAD

#include <fstream>
#include <string>
#include <vector>
#include "Element.hpp"

void save_game(std::vector<Element*> items_list, std::vector<Element*> items_on_map, std::string file_name = "game_save");
void load_game(std::vector<Element*> &items_list, std::vector<Element*> &items_on_map, std::string file_name);
#endif