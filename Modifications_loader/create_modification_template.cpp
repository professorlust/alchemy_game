#include "Modifications_loader.hpp"

void Modifications_loader::create_modification_template()
{
	std::ofstream file("template.txt");

	file
		<< "settings:" << std::endl
		<< "name = \"Template for your game!\"" << std::endl
		<< "author = \"Author name\"" << std::endl
		<< "description = \"^_^\"" << std::endl
		<< std::endl
		<< "images_folder = \"\" # The path to the folder with images looks like this: modifications_folder (from config.ini) + images_folder" << std::endl
		<< "render_top_elements_panel = true" << std::endl
		<< "deletion_elements_RMB = true" << std::endl
		<< std::endl
		<< "colors:" << std::endl
		<< "\"My color\" text(152, 125, 43) background(1, 35, 2)" << std::endl
		<< std::endl
		<< "elements:" << std::endl
		<< "element \"Water\" color(\"Water\")" << std::endl
		<< "element \"Fire\" color(\"Fire\")" << std::endl
		<< "element \"Steam\" color(\"Air\")" << std::endl
		<< std::endl
		<< "reactions:" << std::endl
		<< "Fire + Water = Steam" << std::endl
		<< std::endl
		<< "started_elements:" << std::endl
		<< "Fire" << std::endl
		<< "Water" << std::endl;

		file.close();
}