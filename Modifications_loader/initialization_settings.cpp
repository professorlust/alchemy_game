#include "Modifications_loader.hpp"

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