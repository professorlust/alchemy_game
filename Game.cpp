#include "Game.hpp"

Game::Game()
{
	
}

Game::~Game()
{
	
}

void Game::load_game(std::vector<Element*> &global_element_list, std::vector<Reaction*> &global_reactions_list, std::vector<unsigned int> &global_started_elements)
{
	global_element_list.clear();
	global_reactions_list.clear();

	// Copying elements to main::element_list
	for (int i = 0; i < element_list.size(); ++i)
	{
		global_element_list.push_back(new Element(element_list[i]));
	}

	// Copying reactions to main::reactions_list
	for (int i = 0; i < reactions_list.size(); ++i)
	{
		global_reactions_list.push_back(new Reaction(reactions_list[i]));
	}

	global_started_elements = started_elements;
}

unsigned int Game::get_number_of_elements()
{
	return number_of_elements;
}

unsigned int Game::get_number_of_reactions()
{
	return number_of_reactions;
}

void Game::console_show_information()
{
	std::cout << "Information about mode: " << name.toAnsiString() << std::endl
	<< "Author's name: " << author.toAnsiString() << std::endl
	<< "Number of elements: " << number_of_elements << std::endl
	<< "Number of reactions: " << number_of_reactions << std::endl
	<< "Description: " << description.toAnsiString() << std::endl;
}

void Game::file_show_full_information()
{
	std::ofstream output_file;
	output_file.open(name.toAnsiString() + "_full_information.txt");

	std::string divider = "= = = = = = = = = = = = = = = = = = = = =";
	output_file << "Information about mode " << name.toAnsiString() << std::endl
	<< "Author's name: " << author.toAnsiString() << std::endl
	<< "Description: " << std::endl 
	<< description.toAnsiString() << std::endl
	<< std::endl
	<< "Number of elements: " << number_of_elements << std::endl
	<< "Number of reactions: " << number_of_reactions << std::endl
	<< divider << std::endl;

	output_file << "List of elements: " << std::endl;
	for (int i = 0; i < element_list.size(); ++i)
	{
		output_file << i+1 << ") " << element_list[i].get_name().toAnsiString() << std::endl;
	}
	output_file << divider << std::endl;

	output_file << "List of reactions: " << std::endl
	<< "COMING SOON!";
	output_file.close();
}

void Game::open_all_items(std::vector<Element*> &items)
{
	for (int i = 0; i < items.size(); ++i)
	{
		Element::set_opened(*items[i]);
	}
}