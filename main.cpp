#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "Item.hpp"
#include "Reaction.hpp"
#include "Config.hpp"
#include "standart_games/Standart_games.hpp"
#include "Modifications_loader/Modifications_loader.hpp"
#include "save_and_load.hpp"
#include "console_commands.hpp"

int main(int argc, char const *argv[])
{
	//setlocale(LC_ALL, "Rus"); // tests

	Config::font.loadFromFile(CONFIG.font_name());

	bool debug_commands_is_active = false;
	for (int i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "-debug_commands")
		{
			std::cout << "The developer's commands are activated. Press ~ to start typing" << std::endl;
			debug_commands_is_active = true;
		}
	}

	bool autosaving_is_active = CONFIG.autosave();
	float autosave_timer_max = CONFIG.autosave_timer();
	float autosave_timer = 0;

	Game_settings game_settings;
	std::vector <sf::Texture*> item_textures; // All lists is loaded from the game loader function
	std::vector<Item> items_list;
	std::vector<Item> items_on_map;
	std::vector<Reaction> reactions_list;
	std::vector<unsigned int> reaction_items_IDs; // IDs of the elements that react in this frame
	std::vector<unsigned int> items_to_erase; // Positions of the elements in the array items_on_map to be deleted
	std::vector<Reagent> items_to_spawn; // IDs of the elemenets that will spawn after reaction
	unsigned int open_items_number = 0;

	/* Test */
	// Modifications_loader::load_modification("test", item_textures, items_list, reactions_list, items_to_spawn, game_settings);
	// for (auto & i : items_list)
	// 	i.set_opened();

	Standart_games::charodey(item_textures, items_list, reactions_list, items_to_spawn, game_settings);
	bool save_game_loaded = load_save_game(items_list, open_items_number, items_on_map, "game_save");
	if (save_game_loaded)
		items_to_spawn.clear();

	if (!game_settings.render_top_elements_panel)
		Config::set_borders(sf::FloatRect(0, 0, CONFIG.window_sizes().x, CONFIG.window_sizes().y));

	sf::Clock clock; // World clock
	float time = 0; // Time cash
	float FPS = 0; // Frames per second

	sf::Vector2f cursor_position; // Cursor coordinates
	int32_t selected_item = -1; // -1 == No item selected

	sf::RectangleShape selection_area_rect; // The selection area when the left button is pressed
	selection_area_rect.setPosition(-1, -1);
	selection_area_rect.setFillColor(sf::Color(0, 0, 150, 150)); // Light blue
	selection_area_rect.setSize(sf::Vector2f(1, 1));
	bool selection_area_is_active = false;

	sf::Text item_name_text;  // Item name when hovering over it
	item_name_text.setCharacterSize(16);
	item_name_text.setFillColor(sf::Color(0, 0, 0));
	item_name_text.setFont(Config::font);

	sf::RectangleShape item_name_background; // Background of the name of the item when you hover over it
	item_name_background.setFillColor(sf::Color(200, 200, 200));

	sf::Text number_of_open_items;
	number_of_open_items.setCharacterSize(14);
	number_of_open_items.setFillColor(sf::Color(0, 0, 0));
	number_of_open_items.setFont(Config::font);
	number_of_open_items.setPosition(5, CONFIG.item_side()*2+5);
	// The string will be set after the startup elements appear

	int item_list_page = 0;
	unsigned int number_of_items_in_row = CONFIG.window_sizes().x / CONFIG.item_side();

	sf::Vector2f spawn_center // Center of a circle of spawn of elements
	(
		CONFIG.window_sizes().x / 2,
		(CONFIG.window_sizes().y - Config::borders.top) / 2
	);

	sf::RectangleShape items_list_background; // The rectangle for the array of open elements
	items_list_background.setPosition(0, 0);
	items_list_background.setFillColor(sf::Color(199, 199, 199, 150)); // Light grey
	items_list_background.setSize(sf::Vector2f(CONFIG.window_sizes().x, CONFIG.item_side()*2));

	number_of_open_items.setString("Number of open elements: " + std::to_string(open_items_number) + " / " + std::to_string(items_list.size()));

	sf::RenderWindow window(sf::VideoMode(CONFIG.window_sizes().x, CONFIG.window_sizes().y, 32), "Alchemy", sf::Style::Close);
	window.setFramerateLimit(CONFIG.fps_limit());

	while (window.isOpen())
	{
		cursor_position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Getting cursor position
		time = clock.getElapsedTime().asSeconds();
		FPS = 1.0f / time; // Getting game FPS

		if (autosaving_is_active)
		{
			autosave_timer += time;
			if (autosave_timer >= autosave_timer_max)
			{
				save_game(items_list, items_on_map, "game_save");
				autosave_timer = 0;
			}
		}

		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					if (autosaving_is_active)
						save_game(items_list, items_on_map, "game_save");

					window.close();
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (cursor_position.y < Config::borders.top) // Hit an array of elements
						{
							for (unsigned int i = item_list_page*number_of_items_in_row;
							i < items_list.size();
							++i)
							{
								if (items_list[i].get_rect().contains(cursor_position.x, cursor_position.y) &&
									items_list[i].is_opened() &&
									!items_list[i].is_static())
								{
									float spawn_x = cursor_position.x;
									float spawn_y = Config::borders.top; // Config::borders.top - items_list[i].get_rect().top;
									items_on_map.push_back(Item(items_list[i], sf::Vector2f(spawn_x, spawn_y)));

									selected_item = 0;
									std::swap(items_on_map.back(), items_on_map[0]);

									items_on_map[0].toggle_move(sf::Vector2f(spawn_x, spawn_y));
									break;
								}
							}
						}
						else // for (cursor_position.y < Config::borders.top). Hit an game zone
						{
							selection_area_is_active = true;
							for (unsigned int i = 0; i < items_on_map.size(); ++i)
							{
								if (items_on_map[i].get_rect().contains(cursor_position.x, cursor_position.y))
								{
									if (items_on_map[i].toggle_move(cursor_position))
									{
										selection_area_is_active = false;
										selected_item = 0;
										std::swap(items_on_map[i], items_on_map[0]);
										break;
									}
								}
							}

							if (selection_area_is_active)
								selection_area_rect.setPosition(cursor_position.x, cursor_position.y);
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
							game_settings.deletion_elements_RMB)
					{
						for (unsigned int i = 0; i < items_on_map.size(); ++i)
						{
							if (items_on_map[i].get_rect().contains(cursor_position.x, cursor_position.y) &&
								!items_on_map[i].is_static())
							{
								items_to_erase.push_back(i);
								break;
							}
						}
					}
					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					if (items_on_map.size() != 0)
						items_on_map[0].toggle_move();

					if (selection_area_is_active)
					{
						for (unsigned int i = 0; i < items_on_map.size(); ++i)
						{
							if (selection_area_rect.getGlobalBounds().intersects(items_on_map[i].get_rect()))
							{
								reaction_items_IDs.push_back(items_on_map[i].get_id());
								items_to_erase.push_back(i);
							}
						}
						spawn_center = cursor_position;
 					}
					else if (selected_item >= 0)
					{
						std::vector<unsigned int> temp_reagents(2);
						std::vector<unsigned int> temp_erase_list(2);
						temp_reagents[0] = items_on_map[selected_item].get_id();
						temp_erase_list[0] = selected_item;
						bool was_a_reaction = false;

						for (unsigned int i = 0; i < items_on_map.size(); ++i)
						{
							if (i != selected_item && // Protection against checking the intersection with yourself
								items_on_map[selected_item].check_collision(items_on_map[i].get_rect()))
							{
								temp_reagents[1] = items_on_map[i].get_id();
								temp_erase_list[1] = i;
								std::sort(temp_reagents.begin(), temp_reagents.end());

								for (auto & reaction : reactions_list)
								{
									if (reaction.check_reaction(temp_reagents, true))
									{
										was_a_reaction = true;
										items_to_spawn = reaction.get_output_items();
										items_to_erase = temp_erase_list;

										spawn_center.x = (items_on_map[0].get_rect().left + items_on_map[i].get_rect().left)/2;
										spawn_center.y = (items_on_map[0].get_rect().top + items_on_map[i].get_rect().top)/2;
										break;
									}
								}

							}

							if (was_a_reaction)
								break; // for (int i = 0; i < items_on_map.size(); ++i)
						}
					}

					selected_item = -1;
					selection_area_is_active = false;
					//spawn_center = cursor_position;
					break;
				}

				case sf::Event::KeyReleased:
				{

					if ((event.key.code == sf::Keyboard::W) ||
						(event.key.code == sf::Keyboard::PageUp) ||
						(event.key.code == sf::Keyboard::Up))
					{
						if (item_list_page > 0)
						  item_list_page--;
					}
					else if ((event.key.code == sf::Keyboard::S) ||
						(event.key.code == sf::Keyboard::PageDown) ||
						(event.key.code == sf::Keyboard::Down) )
					{
						if (number_of_items_in_row*(item_list_page+1) < open_items_number)
							item_list_page++;
					}
					else if (event.key.code == sf::Keyboard::F5)
					{
						save_game(items_list, items_on_map, "game_save");
						autosave_timer = 0;
					}
					else if (event.key.code == sf::Keyboard::F4)
						for (unsigned int i = 0; i < items_on_map.size(); ++i)
							items_to_erase.push_back(i);

					/* Activating development commands */
					else if (event.key.code == sf::Keyboard::Tilde
						&& debug_commands_is_active)
						console_command(items_list, reactions_list, game_settings);
				}

				default:
					break;

			} // end of switch
		} // end of while(poolEvent);

		/* Setting real-time size of selection area */

		if (selection_area_is_active)
		{
			// protection against access to the area of opened elements
			float temp_w = cursor_position.x - selection_area_rect.getPosition().x;
			float temp_h = 0;
			temp_h = (cursor_position.y > Config::borders.top) ? cursor_position.y - selection_area_rect.getPosition().y : Config::borders.top - selection_area_rect.getPosition().y;

			selection_area_rect.setSize(sf::Vector2f(temp_w, temp_h));
		}

		/* Check reactions */

		if (!reaction_items_IDs.empty())
		{
			std::sort(reaction_items_IDs.begin(), reaction_items_IDs.end()); // sort the items_on_map

			bool was_a_reaction = false;
			for (auto & reaction : reactions_list)
			{
				if (reaction.check_reaction(reaction_items_IDs, true))
				{
					items_to_spawn = reaction.get_output_items();
					was_a_reaction = true;
				}
			}
			reaction_items_IDs.clear();
			if (!was_a_reaction)
				items_to_erase.clear();
		}

		/* Removal of elements after the reaction */

		if (!items_to_erase.empty())
		{
			std::sort(items_to_erase.begin(), items_to_erase.end());
			unsigned int counter = 0;
			for (unsigned int i = 0; i < items_to_erase.size(); ++i)
			{
				unsigned int del = items_to_erase[i] - counter;
				if (del <= items_on_map.size()-1 &&
					items_on_map.size() != 0 &&
					!items_on_map[del].is_static()) // del can be > items_on_map.size()-1
				{
					items_on_map.erase(items_on_map.begin() + del);
					counter++;
				}
			}
			items_to_erase.clear();
		}

		/* The spawn of new elements */

		if (!items_to_spawn.empty())
		{
			int number = items_to_spawn.size();

			float R = CONFIG.item_side()/2 + CONFIG.item_side()*(number-1)/6,
				angle = 0;

			for (auto & reagent : items_to_spawn)
			{
				for (unsigned int i = 0; i < items_list.size(); ++i)
				{
					sf::Vector2f spawn(0, 0);

					if (reagent.id == items_list[i].get_id() &&
						!items_list[i].is_static())
					{
						if (!reagent.remove) // just spawn new element
						{
							angle += 6.28/number;
							spawn.x = spawn_center.x + R*cos(angle),
							spawn.y = spawn_center.y + R*sin(angle);

							if (!items_list[i].is_opened())
							{
								items_list[i].set_opened();
								open_items_number++;
								number_of_open_items.setString("Number of open elements: " + std::to_string(open_items_number) + " / " + std::to_string(items_list.size()));
							}

							items_on_map.push_back(Item(items_list[i], spawn));

							break;
						}
						else // delete element
						{
							for (int k = 0; k < items_on_map.size(); ++k)
							{
								if (!items_on_map[k].is_static() &&
									reagent.id == items_on_map[k].get_id())
								{
									items_on_map.erase(items_on_map.begin() + k);
									break;
								}
							}
						}
					}
				}
			}
			items_to_spawn.clear();
		}

		window.clear(sf::Color(255, 255, 255));

		if (game_settings.render_top_elements_panel)
			window.draw(number_of_open_items);

		/* Items on map render */

		{ // unnamed namespace
			int32_t temp_render_item_name_num = -1; // Render the element name
			bool temp_contains = false;
			for (int i = items_on_map.size()-1; i >= 0; --i)
			{
				items_on_map[i].update(cursor_position, time);
				items_on_map[i].render(window);

				if (items_on_map[i].rect_contains_cursor(cursor_position) &&
				    items_on_map[i].has_image())
				{
					temp_contains = true;
					temp_render_item_name_num = i;
				}
			}

			if (temp_contains)
			{
				float temp_x = cursor_position.x + 15;
				float temp_y = cursor_position.y + 10;

				item_name_background.setSize(sf::Vector2f(items_on_map[temp_render_item_name_num].get_name().getSize()*10, 19));
				item_name_background.setPosition(temp_x, temp_y);

				item_name_text.setString(items_on_map[temp_render_item_name_num].get_name());
				item_name_text.setPosition(temp_x, temp_y);

				window.draw(item_name_background);
				window.draw(item_name_text);
			}

			if (selection_area_is_active)
				window.draw(selection_area_rect);

			if (game_settings.render_top_elements_panel)
				window.draw(items_list_background);
		} // end of unnamed namespace

		/* Top panel render */

		{ // unnamed namespace
			unsigned int first_item = item_list_page*number_of_items_in_row,
			number_of_render_items = number_of_items_in_row * 2,
			render_number = 0;
			if (game_settings.render_top_elements_panel)
				for (unsigned int i = first_item;
				i < items_list.size() && render_number < number_of_render_items;
				++i)
			{
				float x = 0, y = 0;
				if (items_list[i].is_opened() &&
					!items_list[i].is_static())
				{
					x = (render_number < number_of_items_in_row) ? render_number*CONFIG.item_side() : (render_number-number_of_items_in_row)*CONFIG.item_side();
					y = (render_number < number_of_items_in_row) ? 0 : CONFIG.item_side();
					items_list[i].set_position_hard(sf::Vector2f(x, y));
					items_list[i].render(window);

					render_number++;
				}
			}
		} // end of unnamed namespace

		window.display();
	}

	return 0;
}
