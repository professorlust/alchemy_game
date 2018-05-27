#include "Modifications_loader.hpp"

bool Modifications_loader::load_game_data_from_file()
{
	std::ifstream file(file_name);
	if (!file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	uint8_t block = 0; // settings == 1 / colors == 2 / elements == 3 / reactions == 4 / started_elements == 5
	unsigned long int line = 0;

	while (getline(file, process))
	{
		line++;

		if (process.size() == 0 || // Skipping empty lines
			process[0] == comment_flag)
		{
			process.clear();
			continue;
		}

		if (process == "settings:")
			block = 1;
		else if (process == "colors:")
			block = 2;
		else if (process == "elements:")
			block = 3;
		else if (process == "reactions:")
			block = 4;
		else if (process == "started_elements:")
			block = 5;

		else switch (block)
		{
			case 1:
			{
				initialization_settings();
				break;
			}

			case 2:
			{
				initialization_colors();
				break;
			}

			case 3:
			{
				initialization_items();
				break;
			}

			case 4:
			{
				initialization_reactions();
				break;
			}

			case 5:
			{
				initialization_started_items();
				break;
			}

			default:
				break;
		}

		process.clear();
	}

	return true;
	file.close();
}