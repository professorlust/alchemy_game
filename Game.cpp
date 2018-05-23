#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::load_game(std::vector<Item*> &items_list_copy, std::vector<Reaction*> &reactions_list_copy, std::vector<unsigned int> &started_items_copy)
{
	items_list_copy.clear();
	reactions_list_copy.clear();

	// Copying elements to main list of elements
	for (int i = 0; i < items_list.size(); ++i)
		items_list_copy.push_back(new Item(items_list[i]));

	// Copying reactions to main list reactions
	for (int i = 0; i < reactions_list.size(); ++i)
		reactions_list_copy.push_back(new Reaction(reactions_list[i]));

	started_items_copy = started_items;
}

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
	for (int i = 0; i < items_list.size(); ++i)
		output_file << i+1 << ") " << items_list[i].get_name().toAnsiString() << std::endl;

	output_file << divider << std::endl;

	output_file << "Reactions: " << std::endl;
	for (int i = 0; i < reactions_list.size(); ++i)
	{
		std::vector<unsigned int> input_items = reactions_list[i].get_input_items();
		std::vector<unsigned int> output_items = reactions_list[i].get_output_items();

		output_file << i+1 << ") ";
		/* Output of input reagents */
		for (int j = 0; j < input_items.size(); ++j)
		{
			for (int n = 0; n < items_list.size(); ++n)
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
		for (int j = 0; j < output_items.size(); ++j)
		{
			for (int n = 0; n < items_list.size(); ++n)
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

void Game::open_all_items(std::vector<Item*> &items) const
{
	for (int i = 0; i < items.size(); ++i)
		Item::set_opened(*items[i]);
}
