#include "defines.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "Element.hpp"
#include "Reaction.hpp"
#include "Config.hpp"
#include "standart_games/standart_games.hpp"
#include "save_and_load.hpp"

int main(int argc, char const *argv[])
{
	Config config("Config.ini");
	BORDERS = sf::FloatRect(0, ITEM_DIMENSIONS*2, WINDOW_W, WINDOW_H - ITEM_DIMENSIONS*2);

	std::vector<Element*> items_list; // All lists is loaded from the Game*
	std::vector<Element*> items_on_map;
	std::vector<Reaction*> reactions_list; 
	std::vector<unsigned int> reaction_elements_IDs; // IDs of the elements that react in this frame
	std::vector<unsigned int> items_to_erase; // Positions of the elements in the array items_on_map to be deleted
	std::vector<unsigned int> items_to_spawn; // IDs of the elemenets that will spawn after reaction
	std::vector<sf::Texture*> textures; // Used when downloading a game from a file

	Game *game = new Charodey();
	game->load_game(items_list, reactions_list, items_to_spawn);

	sf::Clock clock; // World clock
	float time = 0; // Time cash
	float FPS = 0; // Frames per second
	int32_t selected_item = -1; // -1 == No item selected

	sf::Vector2f cursor_position; // Cursor coordinates

	sf::RectangleShape selection_area_rect; // The selection area when the left button is pressed
	selection_area_rect.setPosition(-1, -1);
	selection_area_rect.setFillColor(sf::Color(0, 0, 150, 150)); // Light blue
	selection_area_rect.setSize(sf::Vector2f(1, 1));
	bool selection_area_is_active = false;
	
	sf::Text item_name_text;  // Item name when hovering over it
	item_name_text.setCharacterSize(16);
	item_name_text.setFillColor(sf::Color(0, 0, 0));
	item_name_text.setFont(GLOBAL_FONT);

	sf::RectangleShape item_name_background; // Background of the name of the item when you hover over it
	item_name_background.setFillColor(sf::Color(200, 200, 200));

	sf::Text number_of_open_items;
	number_of_open_items.setCharacterSize(14);
	number_of_open_items.setFillColor(sf::Color(0, 0, 0));
	number_of_open_items.setFont(GLOBAL_FONT);
	number_of_open_items.setPosition(5, ITEM_DIMENSIONS*2+5);
	// The string will be set after the startup elements appear

	int item_list_page = 0;

	load_game(items_list, items_on_map, "game_save");

	sf::RectangleShape element_list_background; // The rectangle for the array of open elements
	element_list_background.setPosition(0, 0);
	element_list_background.setFillColor(sf::Color(199, 199, 199, 150)); // Light grey
	element_list_background.setSize(sf::Vector2f(WINDOW_W, ITEM_DIMENSIONS*2));

	/* Spawn of starting elements */
	// A slightly modified code for the appearance of new elements.
	if (items_to_spawn.size() > 0)
	{
		float R = ITEM_DIMENSIONS, angle = 0;
		int number = items_to_spawn.size();
		float spawn_x_center = WINDOW_W / 2, // Center of a circle of spawn of elements
			  spawn_y_center = (WINDOW_H - BORDERS.top) / 2;
		for (int i = 0; i < items_to_spawn.size(); ++i)
		{
			for (int j = 0, spawn_x = 0, spawn_y = 0; j < items_list.size(); ++j)
			{
				if (items_to_spawn[i] == items_list[j]->get_id())
				{
					angle += 6.28/number;
					spawn_x = spawn_x_center + R*cos(angle), 
					spawn_y = spawn_y_center + R*sin(angle);

					Element::set_opened(*items_list[j]);
					items_on_map.push_back(new Element(*items_list[j], sf::Vector2f(spawn_x, spawn_y)));

					break;
				}
			}
		}
		items_to_spawn.clear();
	}
	
	number_of_open_items.setString("Number of open elements: " + std::to_string(Element::get_open_elements_num()) + " / " + std::to_string(items_list.size()));

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H, 32), "AlchemyGame", sf::Style::Close);
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		cursor_position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Getting cursor position
		time = clock.getElapsedTime().asSeconds();
		FPS = 1.0f / time; // Getting game FPS
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					save_game(items_list, items_on_map);
					window.close();
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (cursor_position.y < BORDERS.top) // Hit an array of elements
						{
							for (int i = 0; i < items_list.size(); ++i)
							{
								if (items_list[i]->get_rect().contains(cursor_position.x, cursor_position.y))
								{
									float spawn_x = cursor_position.x;
									float spawn_y = BORDERS.top; // BORDERS.top - items_list[i]->get_rect().top;
									items_on_map.push_back(new Element(*items_list[i], sf::Vector2f(spawn_x, spawn_y)));
									items_on_map[items_on_map.size()-1]->toggle_move(sf::Vector2f(spawn_x, spawn_y));
									selected_item = items_on_map.size()-1;
									break;
								}
							}
						}
						else // for (cursor_position.y < BORDERS.top). Hit an game zone
						{
							selection_area_is_active = true;
							for (int i = 0; i < items_on_map.size(); ++i)
							{
								if (items_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
								{
									if (items_on_map[i]->toggle_move(cursor_position)) 
									{
										selection_area_is_active = false;
										selected_item = i;
										break;
									}
								}
							}
							selection_area_rect.setPosition(cursor_position.x, cursor_position.y);
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						for (int i = 0; i < items_on_map.size(); ++i)
						{
							if (items_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
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
					for (int i = 0; i < items_on_map.size(); ++i)
					{
						if (items_on_map[i]->toggle_move()) 
							break;
					}

					if (selection_area_is_active)
					{
						for (int i = 0; i < items_on_map.size(); ++i)
						{
							if (selection_area_rect.getGlobalBounds().intersects(items_on_map[i]->get_rect()))
							{
								reaction_elements_IDs.push_back(items_on_map[i]->get_id());
								items_to_erase.push_back(i);
							}
						}
					}
					else if (selected_item >= 0)
					{
						std::vector<unsigned int> temp_reagents(2);
						std::vector<unsigned int> temp_erase_list(2);
						temp_reagents[0] = items_on_map[selected_item]->get_id();
						temp_erase_list[0] = selected_item;
						bool was_a_reaction = false;

						for (int i = 0; i < items_on_map.size(); ++i)
						{
							if (i != selected_item & // Protection against checking the intersection with yourself
								items_on_map[selected_item]->check_collision(items_on_map[i]->get_rect()))
							{
								temp_reagents[1] = items_on_map[i]->get_id();
								temp_erase_list[1] = i;
								std::sort(temp_reagents.begin(), temp_reagents.end());
								for (int r = 0; r < reactions_list.size(); ++r)
								{
									if (reactions_list[r]->check_reaction(temp_reagents, true))
									{
										was_a_reaction = true;
										items_to_spawn = reactions_list[r]->get_output_items();
										items_to_erase = temp_erase_list;
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
					break;
				}

				case sf::Event::KeyReleased:
				{
					int number_of_items_in_row = WINDOW_W / ITEM_DIMENSIONS;

					if ((event.key.code == sf::Keyboard::W) ||
						(event.key.code == sf::Keyboard::PageUp) ||
						(event.key.code == sf::Keyboard::Up))
					{
						if (number_of_items_in_row*(item_list_page+1) < Element::get_open_elements_num())
							item_list_page++;
					}
					else if ((event.key.code == sf::Keyboard::S) ||
						(event.key.code == sf::Keyboard::PageDown) ||
						(event.key.code == sf::Keyboard::Down) )
					{
						if (item_list_page > 0)
							item_list_page--;
					}
				}

				default:
					break;

			} // end of switch
		} // end of while(poolEvent);

		// setting real-time size of selection area
		if (selection_area_is_active)
		{
			// protection against access to the area of opened elements
			float temp_w = cursor_position.x - selection_area_rect.getPosition().x;
			float temp_h = 0;
			temp_h = (cursor_position.y > BORDERS.top) ? cursor_position.y - selection_area_rect.getPosition().y : BORDERS.top - selection_area_rect.getPosition().y;

			selection_area_rect.setSize(sf::Vector2f(temp_w, temp_h));
		}

		// Check reactions
		if (reaction_elements_IDs.size() > 0)
		{
			std::sort(reaction_elements_IDs.begin(), reaction_elements_IDs.end()); // sort the items_on_map

			bool was_a_reaction = false;
			for (int i = 0; i < reactions_list.size(); ++i)
			{
				if (reactions_list[i]->check_reaction(reaction_elements_IDs, true))
				{
					items_to_spawn = reactions_list[i]->get_output_items();
					was_a_reaction = true;
				}
			}
			reaction_elements_IDs.clear();
			if (!was_a_reaction) 
				items_to_erase.clear();
		}
		// Removal of elements after the reaction
		if (items_to_erase.size() > 0)
		{
			std::sort(items_to_erase.begin(), items_to_erase.end());
			for (int i = 0; i < items_to_erase.size(); ++i)
				items_on_map.erase(items_on_map.begin() + items_to_erase[i] - i);
			items_to_erase.clear();
		}
		// The spawn of new elements
		if (items_to_spawn.size() > 0)
		{
			float R = ITEM_DIMENSIONS/1.75, angle = 0;
			int number = items_to_spawn.size();

			for (int i = 0; i < items_to_spawn.size(); ++i)
			{
				for (int j = 0, spawn_x, spawn_y; j < items_list.size(); ++j)
				{
					if (items_to_spawn[i] == items_list[j]->get_id() &
						!items_list[j]->is_static())
					{
						angle += 6.28/number;
						spawn_x = cursor_position.x + R*cos(angle), 
						spawn_y = cursor_position.y + R*sin(angle);

						Element::set_opened(*items_list[j]);
						items_on_map.push_back(new Element(*items_list[j], sf::Vector2f(spawn_x, spawn_y)));

						break;
					}
				}
			}
			number_of_open_items.setString("Number of open elements: " + std::to_string(Element::get_open_elements_num()) + " / " + std::to_string(items_list.size()));
			items_to_spawn.clear();
		}

		window.clear(sf::Color(255, 255, 255));

		window.draw(number_of_open_items);

		int32_t temp_render_element_name_num = -1; // Render the element name
		bool temp_contains = false;
		for (int i = items_on_map.size()-1; i >= 0; --i)
		{   
			items_on_map[i]->update(cursor_position, time);
			items_on_map[i]->render(window);

			if (items_on_map[i]->rect_contains_cursor(cursor_position) &
			   (items_on_map[i]->has_image()) )
			{
				temp_contains = true;
				temp_render_element_name_num = i;
			}
		}

		if (temp_contains)
		{
			float temp_x = cursor_position.x + 15;
			float temp_y = cursor_position.y + 10;

			item_name_background.setSize(sf::Vector2f(items_on_map[temp_render_element_name_num]->get_name().getSize()*10, 16));
			item_name_background.setPosition(temp_x, temp_y);

			item_name_text.setString(items_on_map[temp_render_element_name_num]->get_name());
			item_name_text.setPosition(temp_x, temp_y);

			window.draw(item_name_background);
			window.draw(item_name_text);
		}

		if (selection_area_is_active) 
			window.draw(selection_area_rect);

		window.draw(element_list_background);

		/* Top panel render */
		{
			int number_of_items_in_row = WINDOW_W / ITEM_DIMENSIONS;

			unsigned int first_item = item_list_page*number_of_items_in_row,
			number_of_render_items = number_of_items_in_row * 2,
			render_number = 0;

			for (int i = first_item, x = 0, y = 0; 
				i < items_list.size() & render_number < number_of_render_items; 
				++i) // For readability, the line is divided into three lines
			{
				if (items_list[i]->is_opened() &
					!items_list[i]->is_static())
				{
					x = (render_number < number_of_items_in_row) ? render_number*ITEM_DIMENSIONS : (render_number-number_of_items_in_row)*ITEM_DIMENSIONS;
					y = (render_number < number_of_items_in_row) ? 0 : ITEM_DIMENSIONS;
					items_list[i]->set_position_hard(sf::Vector2f(x, y));
					items_list[i]->render(window);

					render_number++;
				}
			}
		} // end of unnamed namespace

		window.display();
	}

	return 0;
}
