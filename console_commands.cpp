#include "console_commands.hpp"

void console_command(std::vector<Item*> &items_list, Game *game)
{
	bool is_active = true;

	while (is_active)
	{
	std::string input_string;
	std::cout << "Enter the command. Use the \"help\" to get a list of commands: ";
	std::cin >> input_string;

	if (input_string == "help")
		std::cout << "List of commands:" << std::endl
		<< "open_all: Opens all the elements in the game" << std::endl
		<< "get_full_game_information: Creates a file with information about the running game" << std::endl
		<< "new_game: Load new game from file (or standart game)" << std::endl
		<< "exit: Close console input" << std::endl;

	else if (input_string == "open_all")
		game->open_all_items(items_list);

	else if (input_string == "get_full_game_information")
		game->file_show_full_information();

	else if (input_string == "new_game")
	{
		std::cout << "Choose a game (enter its number or 0 to close this menu)" << std::endl
		<< "1) Charodey" << std::endl
		<< "2) Load a game from file" << std::endl;
		
		int number = 0;
		std::cin << number;

	}

	else if (input_string == "exit")
		is_active = false;

	else
		std::cout << "Unknown command. Use the \"help\" to get a list of commands" << std::endl;
	}
}