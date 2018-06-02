#include "Modifications_loader.hpp"

void Modifications_loader::initialization_colors()
{
	if (process.size() == 0)
		return;

	unsigned int symbol = 1; // skip the """
	std::string parameter;

	Item_color new_item_color = {"", sf::Color(255, 255, 255), sf::Color(0, 0, 0)};

	removing_spaces();

	if (process[0] != '"')
	{
		std::cout << "Color process error. First symbol is not \'\"\'." << std::endl;
		return;
	}

	/* Getting name */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag &&
		   process[symbol] != '"')
	{
		new_item_color.name += process[symbol];
		symbol++;
	}
	symbol++; // skip the """

	for (int i = 0; i < 2 && symbol < process.size(); ++i)
	{
		std::string argument; // argument (background / text)
		while (process[symbol] != '(' &&
			   process[symbol] != ')')
		{
			argument += process[symbol];
			symbol++;
		}
		symbol++; // skip the symbol (

		std::string r_string;
		while (process[symbol] != ',' &&
			   process[symbol] != ')')
		{
			r_string += process[symbol];
			symbol++;
		}
		symbol++; // skip the symbol ,

		std::string g_string;
		while (process[symbol] != ',' &&
			   process[symbol] != ')')
		{
			g_string += process[symbol];
			symbol++;
		}
		symbol++; // skip the symbol ,

		std::string b_string;
		while (process[symbol] != ',' &&
			   process[symbol] != ')')
		{
			b_string += process[symbol];
			symbol++;
		}
		symbol++; // skip the symbol ,

		if (argument == "background")
			new_item_color.background = sf::Color(atoi(r_string.c_str()), atoi(g_string.c_str()), atoi(b_string.c_str()));
		else if (argument == "text")
			new_item_color.text = sf::Color(atoi(r_string.c_str()), atoi(g_string.c_str()), atoi(b_string.c_str()));
		else
			std::cout << "Color process error: " << argument << " - unknown argument." << std::endl;
	}

	item_colors.push_back(new_item_color);
}