#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

/* General methods */

void Game::load_game(std::vector<Item*> &items_list_copy, std::vector<Reaction*> &reactions_list_copy, std::vector<Reagent> &started_items_copy)
{
	items_list_copy.clear();
	reactions_list_copy.clear();

	// Copying elements to main list of elements
	for (auto & item : items_list)
		items_list_copy.push_back(new Item(item));

	// Copying reactions to main list reactions
	for (auto & reaction : reactions_list)
		reactions_list_copy.push_back(new Reaction(reaction));

	for (auto & i : started_items)
	{
		started_items_copy.push_back(Reagent());
		started_items_copy[started_items_copy.size()-1].id = i;
	}
}

/* Methods for obtaining data. All methods are CONST */

unsigned int Game::get_number_of_items() const
{
	return number_of_items;
}

unsigned int Game::get_number_of_reactions() const
{
	return number_of_reactions;
}

sf::String Game::get_game_name() const
{
	return name;
}

bool Game::deletion_elements_RMB() const
{
	return deletion_elements_RMB_;
}

void Game::console_show_information() const
{
	std::cout << name.toAnsiString() << std::endl
	<< "Author: " << author.toAnsiString() << std::endl
	<< number_of_items << " element(s)" << std::endl
	<< number_of_reactions << " reaction(s)" << std::endl
	<< "Description: " << description.toAnsiString() << std::endl;
}

void Game::file_show_full_information() const
{
	std::ofstream output_file;
	output_file.open(name.toAnsiString() + "_full_information.txt");

	std::string divider = "= = = = = = = = = = = = = = = = = = = = =";

	output_file << name.toAnsiString() << std::endl
	<< "Author: " << author.toAnsiString() << std::endl
	<< "Description: " << std::endl
	<< description.toAnsiString() << std::endl
	<< std::endl
	<< number_of_items << " element(s)" << std::endl
	<< number_of_reactions << " reaction(s)" << std::endl
	<< divider << std::endl;

	output_file << "Items: " << std::endl;
	for (unsigned int i = 0; i < items_list.size(); ++i)
		output_file << i+1 << ") " << items_list[i].get_name().toAnsiString() << std::endl;

	output_file << divider << std::endl;

	output_file << "Reactions: " << std::endl
	<< "Temporarily does not display information about the conditions for the appearance of elements!" << std::endl;

	for (unsigned int i = 0; i < reactions_list.size(); ++i)
	{
		std::vector<unsigned int> input_items = reactions_list[i].get_input_items();
		std::vector<unsigned int> output_items;

		for (auto & i : reactions_list[i].get_output_items())
			output_items.push_back(i.id);

		output_file << i+1 << ") ";
		/* Output of input reagents */
		for (unsigned int j = 0; j < input_items.size(); ++j)
		{
			for (unsigned int n = 0; n < items_list.size(); ++n)
			{
				if (input_items[j] == items_list[n].get_id())
				{
					output_file << items_list[n].get_name().toAnsiString();
					if (j != input_items.size()-1)
						output_file << " + ";
				}
			}
		}
		output_file << " = ";

		/* Output of output reagents. Strange phrase */
		for (unsigned int j = 0; j < output_items.size(); ++j)
		{
			for (unsigned int n = 0; n < items_list.size(); ++n)
			{
				if (output_items[j] == items_list[n].get_id())
				{
					output_file << items_list[n].get_name().toAnsiString();
					if (j != output_items.size()-1)
						output_file << " + ";
				}
			}
		}
		output_file << std::endl;
	}

	output_file.close();
}
