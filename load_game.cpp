#include "save_and_load.hpp"

void load_game(std::vector<Element*> &items_list, std::vector<Element*> &items_on_map, std::string file_name)
{
	std::ifstream save_file(file_name);
	if (!save_file.is_open())
	{
		std::cout << "File not found!";
		return;
	}

	/* Load open items */
	std::string input_line, buffer;
	std::getline(save_file, input_line);
	std::cout << input_line;
	/* Load items on map */
	while (std::getline(save_file, input_line))
	{
		// std::cout << input_line << std::endl;
	}
}