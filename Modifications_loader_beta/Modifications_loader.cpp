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

/* Static methods */
void Modifications_loader::create_modification_template()
{
	std::ofstream file("modification_template.txt");

	file
		<< "settings:" << std::endl
		<< "modification_name = \"Modification name\"" << std::endl
		<< "modification_author = \"Author name\"" << std::endl
		<< "modification_description = \"Description. It's a long story\"" << std::endl
		<< "modification_image_folder_name = \"Folder\" # Full path to the image folder: modifications_folder (from config.ini) + modification_image_folder_name"  << std::endl
		<< std::endl
		<< "top_element_panel = true" << std::endl
		<< "deletion_elements_RMB = true # Deletion elements by pressing the RMB" << std::endl
		<< std::endl
		<< "# Do not use Russian letters! ! !" << std::endl
		<< "# They do not work correctly at the this moment" << std::endl
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
