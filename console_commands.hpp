#ifndef CONSOLE_COMMANDS_HPP
#define CONSOLE_COMMANDS_HPP

#include <iostream>
#include <string>

#include "Item.hpp"
#include "Reaction.hpp"
#include "Game.hpp"
#include "Modifications_loader/Modifications_loader.hpp"

void console_command(std::vector<Item> &items_list, std::vector<Reaction> &reactions_list, Game* game);

#endif