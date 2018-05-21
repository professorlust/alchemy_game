#ifndef CONSOLE_COMMANDS_HPP
#define CONSOLE_COMMANDS_HPP

#include <iostream>
#include <string>

#include "Item.hpp"
#include "Game.hpp"

void console_command(std::vector<Item*> &items_list, Game *game);

#endif