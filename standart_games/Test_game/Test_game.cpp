#include "Test_game.hpp"

Test_game::Test_game()
{
	initialization_textures();
	initialization_elements();
	initialization_reactions();
	initialization_started_elements();

	number_of_elements = element_list.size();
	number_of_reactions = reactions_list.size();

	name = "Test_game";
	author = "default";
	description = "";
}

void Test_game::initialization_textures()
{

}

void Test_game::initialization_elements()
{
	/* Demonstration of colors */
	element_list.emplace_back("AIR_COLOR", "", 1, AIR_COLOR);
	element_list.emplace_back("FIRE_COLOR", "", 2, FIRE_COLOR);
	element_list.emplace_back("EARTH_COLOR", "", 3, EARTH_COLOR);
	element_list.emplace_back("WATER_COLOR", "", 4, WATER_COLOR);
	element_list.emplace_back("LIGHT_GREEN_COLOR", "", 5, LIGHT_GREEN_COLOR);
	element_list.emplace_back("PURPLE_COLOR", "", 6, PURPLE_COLOR);
	element_list.emplace_back("GREY_COLOR", "", 7, GREY_COLOR);
	element_list.emplace_back("LIGHT_PINK_COLOR", "", 8, LIGHT_PINK_COLOR);
	element_list.emplace_back("DARK_COLOR", "", 9, DARK_COLOR);
	element_list.emplace_back("DARK_RED_COLOR", "", 10, DARK_RED_COLOR);
	element_list.emplace_back("DARK_BLUE_COLOR", "", 11, DARK_BLUE_COLOR);
	element_list.emplace_back("DARK_GREEN_COLOR", "", 12, DARK_GREEN_COLOR);
}

void Test_game::initialization_reactions()
{

}

void Test_game::initialization_started_elements()
{
	for (int i = 0; i < element_list.size(); ++i)
	{
		started_elements.push_back(element_list[i].get_id());
	}
}