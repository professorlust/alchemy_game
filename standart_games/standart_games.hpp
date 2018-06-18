#ifndef STANDART_GAMES
#define STANDART_GAMES

#include "../Game_settings.hpp"
#include "../Item.hpp"
#include "../Reaction.hpp"
#include "../Reagent.hpp"
#include "../Item_color.hpp"
#include "../Config.hpp"

#include <vector>

namespace Standart_games
{
	void charodey(std::vector<sf::Texture> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy, Game_settings &game_settings);
}
#endif