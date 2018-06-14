#include "console_commands.hpp"

void console_command(std::vector<Item> &items_list, std::vector<Reaction> &reactions_list, Game game)
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
		//<< "get_full_game_information: Creates a file with information about the running game" << std::endl
		<< "create_modification_template: Creates a template with a modification code" << std::endl
		<< "exit: Close console input" << std::endl;

	else if (input_string == "open_all")
		for (unsigned int i = 0; i < items_list.size(); ++i)
			items_list[i].set_opened();


	// else if (input_string == "get_full_game_information")
	// 	game.file_show_full_information();

	else if (input_string == "create_modification_template")
		Modifications_loader::create_modification_template();

	else if (input_string == "exit")
		is_active = false;

	else
		std::cout << "Unknown command. Use the \"help\" to get a list of commands" << std::endl;
	}
}