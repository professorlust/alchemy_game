#include "Modifications_loader.hpp"

void Modifications_loader::initialization_items()
{
	if (process.size() == 0)
		return;

	unsigned int symbol = 0;
	std::string parameter;

	sf::String name;
	bool is_static = false;
	bool has_image = false;

	std::string type_string;
	int8_t type = 0; // element == 1 / counter == 2 / timer == 3...

	Item_color item_color;

	/* Getting element type */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag &&
		   process[symbol] != ' ')
	{
		type_string += process[symbol];
		symbol++;
	}
	symbol++; // skip the " "

	if (type_string == "element")
		type = 1;
	else if (type_string == "counter")
		type = 2;
	else if (type_string == "timer")
		type = 3;
	else if (type_string.size() != 0)
	{
		std::cout << "Element process error. " << type_string << ": unknown type." << std::endl;
		return;
	}

	/* Getting name */
	// skip the blank space
	while (symbol < process.size() &&
	   process[symbol] != comment_flag &&
	   process[symbol] != '"')
		symbol++;

	symbol++; // skip the """

	while (symbol < process.size() &&
		   process[symbol] != comment_flag &&
		   process[symbol] != '"')
	{
		name += process[symbol];
		symbol++;
	}
	symbol += 2; // skip the """ and blank space

	bool in_quotes = false;
	/* Getting parameters */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag)
	{
		if (process[symbol] == '(' || process[symbol] == ')')
			in_quotes = !in_quotes;

		if (process[symbol] != ' ' || in_quotes)
			parameter += process[symbol];
		symbol++;

		if ((process[symbol] == ' ' && !in_quotes) ||
			symbol == process.size()) // Blank space is delimiter of parameters
		{
			std::string parameter_string, parameter_value;
			unsigned int i = 0;

			while (parameter[i] != '(' &&
				   i < parameter.size())
			{
				parameter_string += parameter[i];
				i++;
			}
			i++; // skip the '('

			while (parameter[i] != ')' &&
				   i < parameter.size())
			{
				parameter_value += parameter[i];
				i++;
			}
			i++; // skip the ')'

			if (parameter_string == "static")
				is_static = true;

			else if (parameter_string == "image" &&
					 !has_image)
			{
				has_image = true;
				textures.push_back(new sf::Texture());
				textures[textures.size()-1]->loadFromFile(CONFIG.modifications_folder()+'/'+modification_image_folder_name+'/'+parameter_value);
			}

			else if (parameter_string == "color")
			{
				if (parameter_value == "Air")
					item_color = AIR_COLOR;
				else if (parameter_value == "Fire")
					item_color = FIRE_COLOR;
				else if (parameter_value == "Earth")
					item_color = EARTH_COLOR;
				else if (parameter_value == "Water")
					item_color = WATER_COLOR;
				else if (parameter_value == "Light green")
					item_color = LIGHT_GREEN_COLOR;
				else if (parameter_value == "Purple")
					item_color = PURPLE_COLOR;
				else if (parameter_value == "Grey")
					item_color = GREY_COLOR;
				else if (parameter_value == "Light pink")
					item_color = LIGHT_PINK_COLOR;
				else if (parameter_value == "Dark")
					item_color = DARK_COLOR;
				else if (parameter_value == "Dark blue")
					item_color = DARK_RED_COLOR;
				else if (parameter_value == "Orange")
					item_color = ORANGE_COLOR;
				else if (parameter_value == "Dark green")
					item_color = DARK_GREEN_COLOR;

				else for (int i = 0; i < item_colors.size(); ++i)
				{
					if (item_colors[i].name == parameter_value)
					{
						item_color = item_colors[i];
						break;
					}
				}
			}
			parameter.clear();
		}
	}

	if (has_image)
		items_list.emplace_back(textures[textures.size()-1], name, "", items_list.size()+1, item_color, is_static);
	else
		items_list.emplace_back(name, "", items_list.size()+1, item_color, is_static);
}