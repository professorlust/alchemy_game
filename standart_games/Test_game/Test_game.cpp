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
	element_list.emplace_back("NONE", "", 1, NONE);
	element_list.emplace_back("AIR", "", 2, AIR);
	element_list.emplace_back("WATER", "", 3, WATER);
	element_list.emplace_back("FIRE", "", 4, FIRE);
	element_list.emplace_back("EARTH", "", 5, EARTH);
	element_list.emplace_back("PLANT", "", 6, PLANT);
	element_list.emplace_back("ANIMAL", "", 7, ANIMAL);
	element_list.emplace_back("MAGIC", "", 8, MAGIC);
	element_list.emplace_back("CIVILIZATION", "", 9, CIVILIZATION);
	element_list.emplace_back("HUMAN", "", 10, HUMAN);
	element_list.emplace_back("FOOD", "", 11, FOOD);
	element_list.emplace_back("DARK", "", 12, DARK);
	element_list.emplace_back("OTHER", "", 13, OTHER);
	element_list.emplace_back("DARK_BLUE", "", 14, DARK_BLUE);
	element_list.emplace_back("CRIMSON", "", 15, CRIMSON);
	element_list.emplace_back("ORANGE", "", 16, ORANGE);
	element_list.emplace_back("JUNGLE", "", 17, JUNGLE);
	element_list.emplace_back("EVIL", "", 18, EVIL);
}

void Test_game::initialization_reactions()
{

}

void Test_game::initialization_started_elements()
{
	for (int i = 0; i < element_list.size(); ++i)
	{
		started_elements.push_back(i);
	}
}