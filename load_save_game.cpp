#include "save_and_load.hpp"

bool load_save_game(std::vector<Item*> &items_list, unsigned int &open_items_number, std::vector<Item*> &items_on_map, std::string file_name)
{
	std::ifstream save_file(file_name);
	if (!save_file.is_open())
	{
		std::cout << "Load save game error: File not found!" << std::endl;
		return false;
	}

	/* Load open items */
	std::string input_line, buffer;
	std::getline(save_file, input_line);
	open_items_number = 0;

	for (unsigned int i = 0; i < input_line.size(); ++i)
	{
		while (input_line[i] != ' ') // getting the item ID
		{
			buffer += input_line[i];
			i++;
		}

		unsigned int item_id = atoi(buffer.c_str());

		for (unsigned int i = 0; i < items_list.size(); ++i)
		{
			if (item_id == items_list[i]->get_id())
			{
				items_list[i]->set_opened();
				open_items_number++;
			}
		}
		buffer.clear();
	}

	/* Getting items on the map */
	while (std::getline(save_file, input_line))
	{
		int i = 0;

		while (input_line[i] != ' ') // getting the item ID
		{
			buffer += input_line[i];
			i++;
		}
		i++;
		unsigned int item_id = atoi(buffer.c_str());
		buffer.clear();

		sf::Vector2f spawn(0, 0);

		while (input_line[i] != ' ') // getting spawn x
		{
			buffer += input_line[i];
			i++;
		}
		i++;
		spawn.x = atoi(buffer.c_str());
		buffer.clear();

		while (input_line[i] != ' ') // getting spawn y
		{
			buffer += input_line[i];
			i++;
		}
		i++;
		spawn.y = atoi(buffer.c_str());
		buffer.clear();

		for (auto & item : items_list)
		{
			if (item_id == item->get_id())
			{
				items_on_map.push_back(new Item(*item, spawn));
				break;
			}
		}
	}

	return true;
}