#include "save_and_load.hpp"

bool load_game(std::vector<Element*> &items_list, std::vector<Element*> &items_on_map, std::string file_name)
{
	std::ifstream save_file(file_name);
	if (!save_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	/* Load open items */
	std::string input_line, buffer;
	std::getline(save_file, input_line);

	for (int i = 0; i < input_line.size(); ++i)
	{
		while (input_line[i] != ' ') // getting the item ID
		{
			buffer += input_line[i];
			i++;
		}

		int item_id = atoi(buffer.c_str());

		for (int i = 0; i < items_list.size(); ++i)
		{
			if (item_id == items_list[i]->get_id())
			{
				Element::set_opened(*items_list[i]);
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
		int item_id = atoi(buffer.c_str());
		buffer.clear();

		while (input_line[i] != ' ') // getting the item ID
		{
			buffer += input_line[i];
			i++;
		}
		i++;
		int x = atoi(buffer.c_str());
		buffer.clear();

		while (input_line[i] != ' ') // getting the item ID
		{
			buffer += input_line[i];
			i++;
		}
		i++;
		int y = atoi(buffer.c_str());
		buffer.clear();

		for (int j = 0; j < items_list.size(); ++j)
		{
			if (item_id == items_list[j]->get_id())
			{
				items_on_map.push_back(new Element(*items_list[j], sf::Vector2f(x, y)));
			}
		}
	}

	return true;
}