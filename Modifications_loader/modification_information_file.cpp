#include "Modifications_loader.hpp"

void Modifications_loader::modification_information_file(const std::vector<Item> &items_list, const std::vector<Reaction> &reactions_list, const std::vector<Reagent> &started_items, const Game_settings &game_settings)
{
	std::wofstream file("modification_information.txt");

	file
		<< L"Name: " << game_settings.name.toWideString() << std::endl
		<< L"Author: " << game_settings.author.toWideString() << std::endl
		<< L"Description: " << game_settings.author.toWideString() << std::endl
		<< std::endl
		<< items_list.size() << L" element(s)" << std::endl
		<< reactions_list.size() << L" reaction(s)" << std::endl
		<< std::endl
		<< L"List of elements:" << std::endl;

	{
		unsigned int counter = 1;
		for (auto & item : items_list)
		{
			file << counter << ") " << item.get_name().toWideString() << L" [element]";

			if (item.is_static())
				file << L" [static]";

			file << std::endl;
			counter++;
		}
	}

	file
		<< std::endl
		<< L"List of reactions: " << std::endl;

	unsigned int counter = 0;
	for (auto & reaction : reactions_list)
	{
		file << counter << L") ";

		for (unsigned int i = 0; i < reaction.get_input_items().size(); ++i)
		{
			unsigned int id = reaction.get_input_items()[i];
			file << get_item_name_by_id(id, items_list).toWideString() << L" ";

			if (i != reaction.get_input_items().size()-1)
				file << L"+ ";
		}

		file << L"= ";

		for (unsigned int i = 0; i < reaction.get_output_items().size(); ++i)
		{
			Reagent reagent = reaction.get_output_items()[i];

			file << get_item_name_by_id(reagent.id, items_list).toWideString();

			if (reagent.remove)
				file << L"[delete]";

			if (!reagent.found_on_map.empty() ||
				!reagent.not_found_on_map.empty())
			{
				file << L"[";

				file << L"IF: ";

				if (!reagent.found_on_map.empty())
				{
					file << L"Found element(s) on map[";
					for (int j = 0; j < reagent.found_on_map.size(); ++j)
					{
						file << L"\"" << get_item_name_by_id(reagent.found_on_map[j], items_list).toWideString() << L"\"";

						if (j != reagent.found_on_map.size()-1)
							 file << L" ";
					}

					file << L"]";
				}

				if (!reagent.not_found_on_map.empty())
				{
					file << L"Not found element(s) on map[";
					for (int j = 0; j < reagent.not_found_on_map.size(); ++j)
					{
						file << L"\"" << get_item_name_by_id(reagent.not_found_on_map[j], items_list).toWideString() << L"\"";

						if (j != reagent.not_found_on_map.size()-1)
							 file << L" ";
					}

					file << L"]";
				}
			}

			file << L" ";

			if (i != reaction.get_output_items().size()-1)
				file << L"+ ";
		}

		file << std::endl;
		counter++;
	}

	file.close();
}