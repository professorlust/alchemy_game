#include "save_and_load.hpp"

void save_game(std::vector<Item> items_list, std::vector<Item> items_on_map, std::string file_name)
{
	std::ofstream save_file(file_name);

	// Sending ID of open items in a save file
	for (auto & item : items_list)
	{
		if (item.is_opened())
			save_file << item.get_id() << " ";
	}
	save_file << std::endl;

	// Saving information about items on the map
	for (auto & item : items_on_map)
	{
		save_file << item.get_id() << " " << item.get_rect().left << " " << item.get_rect().top << std::endl;
	}
}