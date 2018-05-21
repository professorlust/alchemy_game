#include "save_and_load.hpp"

void save_game(std::vector<Item*> items_list, std::vector<Item*> items_on_map, std::string file_name)
{
	std::ofstream save_file(file_name);

	/* Sending ID of open items in a save file */
	for (int i = 0; i < items_list.size(); ++i)
	{
		if (items_list[i]->is_opened())
			save_file << items_list[i]->get_id() << " ";
	}
	save_file << std::endl;

	/* Saving information about items on the map */
	for (int i = 0; i < items_on_map.size(); ++i)
	{
		save_file << items_on_map[i]->get_id() << " " << items_on_map[i]->get_rect().left << " " << items_on_map[i]->get_rect().top << std::endl;
	}
}