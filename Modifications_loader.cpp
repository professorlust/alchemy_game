#include "Modifications_loader.hpp"

Modifications_loader::Modifications_loader(std::string file)
{
	file_name = file;
	load_game_data_from_file();

	initialization_textures();
	initialization_items();
	initialization_reactions();
	initialization_started_items();

	number_of_items = items_list.size();
	number_of_reactions = reactions_list.size();
}

Modifications_loader::~Modifications_loader()
{

}

void Modifications_loader::initialization_textures()
{

}

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

void Modifications_loader::initialization_reactions()
{
	if (process.size() == 0)
		return;

	unsigned int symbol = 1; // skip first """
	std::string item_name;

	std::vector<unsigned int> input_reagents;
	std::vector<unsigned int> output_reagents;

	std::string buffer_name;

	bool in_quotes = true;

	removing_spaces();

	/* Getting input reagents */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag &&
		   process[symbol] != '=')
	{
		if (in_quotes &&
			process[symbol] != '"')
			buffer_name += process[symbol];

		if (process[symbol] == '"')
		{
			in_quotes = !in_quotes;

			bool item_found = false;
			for (int i = 0; i < items_list.size(); ++i)
			{
				if (items_list[i].get_name() == buffer_name)
				{
					input_reagents.push_back(items_list[i].get_id());
					item_found = true;
					break;
				}
			}
			if (!item_found &&
				buffer_name.size() != 0)
				std::cout << buffer_name << ": element not found." << std::endl;
			buffer_name.clear();
		}
		symbol++;
	}
	symbol++; // skip the '='

	/* Getting output reagents */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag)
	{
		if (in_quotes &&
			process[symbol] != '"')
			buffer_name += process[symbol];

		if (process[symbol] == '"')
		{
			in_quotes = !in_quotes;

			bool item_found = false;
			for (int i = 0; i < items_list.size(); ++i)
			{
				if (items_list[i].get_name() == buffer_name)
				{
					output_reagents.push_back(items_list[i].get_id());
					item_found = true;
					break;
				}
			}
			if (!item_found &&
				buffer_name.size() != 0)
				std::cout << buffer_name << ": element not found." << std::endl;
			buffer_name.clear();
		}
		symbol++;
	}

	reactions_list.push_back(Reaction(input_reagents, output_reagents));
}

void Modifications_loader::initialization_started_items()
{
	if (process.size() == 0)
		return;

	std::string item_name = process;

	for (int i = 0; i < items_list.size(); ++i)
		if (item_name == items_list[i].get_name())
		{
			started_items.push_back(items_list[i].get_id());
			return;
		}

	// if name not found
	std::cout << process << ": started item not found." << std::endl;
}

void Modifications_loader::initialization_settings()
{
	if (process.size() == 0)
		return;

	unsigned int symbol = 0;
	std::string parameter, value;

	removing_spaces();

	/* Getting parameter */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag &&
		   process[symbol] != '=')
	{
		parameter += process[symbol];
		symbol++;
	}
	symbol++; // skip the "="

	/* Getting value of parameter */
	while (symbol < process.size() &&
		   process[symbol] != comment_flag)
	{
		if (process[symbol] != '"')
			value += process[symbol];

		symbol++;
	}

	if (parameter == "top_element_panel") // standart value: TRUE
		top_element_panel_ = (value == "false" || value == "0") ? false : true;
	else if (parameter == "deletion_elements_RMB")
		deletion_elements_RMB_ = (value == "false" || value == "0") ? false : true;

	/* Modification information */
	else if (parameter == "modification_name")
		name = value;
	else if (parameter == "modification_author")
		author = value;
	else if (parameter == "modification_description")
		description = value;
	else if (parameter == "modification_image_folder_name")
		modification_image_folder_name = value;
	else
		std::cout << "Settings process error. " << parameter << ": unknown parameter." << std::endl;
}

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

void Modifications_loader::removing_spaces()
{
	if (process.size() == 0)
		return;

	bool in_quotes = false;
	unsigned int i = 0;

	while (i < process.size())
	{
		if (process[i] == '"')
			in_quotes = !in_quotes;

		if (process[i] == ' ' &&
			!in_quotes)
			process.erase(process.begin()+i);
		else
			i++;
	}
}

void Modifications_loader::create_modification_template()
{
	std::ofstream file("modification_template.txt");

	file
		<< "settings:" << std::endl
		<< "modification_name = \"test game\"" << std::endl
		<< "modification_author = \"author name\"" << std::endl
		<< "modification_description = \"Description. It's a long story\"" << std::endl
		<< "modification_image_folder_name = \"folder name\" # Full path to the image folder: modifications_folder (from config.ini) + modification_image_folder_name"  << std::endl
		<< std::endl
		<< "top_element_panel = true" << std::endl
		<< "deletion_elements_RMB = true # Deletion elements by pressing the RMB"
		<< std::endl
		<< "colors:" << std::endl
		<< "# Put your colors here" << std::endl
		<< std::endl
		<< "elements:" << std::endl
		<< "# Put your elements here" << std::endl
		<< std::endl
		<< "reactions:" << std::endl
		<< "# Put your reactions here" << std::endl
		<< std::endl
		<< "started_elements:" << std::endl
		<< "# Put your started elements here" << std::endl
		<< std::endl;
}