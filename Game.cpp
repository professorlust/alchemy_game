#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

/* Methods for obtaining data. All methods are CONST */

sf::String Game::get_game_name() const
{
	return name;
}

bool Game::deletion_elements_RMB() const
{
	return deletion_elements_RMB_;
}

bool Game::render_top_elements_panel() const
{
	return top_element_panel_;
}
