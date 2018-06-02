#include "Modifications_loader.hpp"

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