#include "defines.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "main.hpp"

int main(int argc, char const *argv[])
{
	std::ifstream config_ini; // COMING SOON NAVERNOE
	config_ini.open("config.ini");
	if (config_ini)
	{
	}
	else
	{
	}
	config_ini.close();

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H, 32), "AlchemyGame", sf::Style::Close);
	window.setFramerateLimit(30);

	sf::Clock clock; // World clock
	float time = 0; // Time cash
	float FPS = 0; // Frames per second

	sf::Vector2f cursor_position; // Cursor coordinates

	std::vector<Element*> elements_list; // All lists is loaded from the Game*
	std::vector<Element*> elements_on_map;
	std::vector<Reaction*> reactions_list; 
	std::vector<unsigned int> reaction_elements_IDs; // IDs of the elements that react in this frame
	std::vector<unsigned int> elements_to_erase; // Positions of the elements in the array elements_on_map to be deleted
	std::vector<unsigned int> elements_to_spawn; // IDs of the elemenets that will spawn after reaction
	//std::vector<sf::Texture*> textures; // Used when downloading a game from a file

	sf::RectangleShape selection_area_rect; // The selection area when the left button is pressed
	selection_area_rect.setPosition(-1, -1);
	selection_area_rect.setFillColor(sf::Color(0, 0, 150, 150)); // Light blue
	selection_area_rect.setSize(sf::Vector2f(1, 1));
	bool selection_area_is_active = false;

	sf::RectangleShape element_list_background; // The rectangle for the array of open elements
	element_list_background.setPosition(0, 0);
	element_list_background.setFillColor(sf::Color(199, 199, 199, 150)); // Light grey
	element_list_background.setSize(sf::Vector2f(WINDOW_W, ELEMENT_DIMENSIONS*2));

	/* Loading of the game */
	Game *game = new Charodey();
	game->load_game(elements_list, reactions_list, elements_to_spawn);

	/* The spawn of new elements */
	if (elements_to_spawn.size() > 0)
	{
		float R = 32 * elements_to_spawn.size(); // Radious of sp
		float angle = 0;
		for (int i = 0; i < elements_to_spawn.size(); ++i)
		{
			for (int j = 0, spawn_x, spawn_y; j < elements_list.size(); ++j)
			{
				if (elements_to_spawn[i] == elements_list[j]->get_id())
				{
					spawn_x = WINDOW_W/2 + R*cos(angle), 
					spawn_y = WINDOW_H/2 + R*sin(angle);
					angle += 6.28 / elements_to_spawn.size();
					spawn_element(elements_list[j], &elements_on_map, spawn_x, spawn_y);

					break;
				}
			}
		}
		elements_to_spawn.clear();
	}

	sf::Font global_font;
	global_font.loadFromFile("Arial.ttf");
	Element::initialization(&global_font);

	int item_list_page = 0;

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
					window.close();
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (cursor_position.y < Y_TOP_BORDER_LINE) // Hit an array of elements
						{
							for (int i = 0; i < elements_list.size(); ++i)
							{
								if (elements_list[i]->get_rect().contains(cursor_position.x, cursor_position.y))
								{
									if (spawn_element(elements_list[i], &elements_on_map, cursor_position.x, cursor_position.y))
									{
										elements_on_map[elements_on_map.size()-1]->enable_move(0, 0);
									}
									break;
								}
							}
						}
						else // for (cursor_position.y < Y_TOP_BORDER_LINE). Hit an game zone
						{
							selection_area_is_active = true;
							for (int i = 0; i < elements_on_map.size(); ++i)
							{
								if (elements_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
								{
									int defection_x = cursor_position.x - elements_on_map[i]->get_rect().left;
									int defection_y = cursor_position.y - elements_on_map[i]->get_rect().top;
									if (elements_on_map[i]->enable_move(defection_x, defection_y)) 
									{
										selection_area_is_active = false;
										break;
									}
								}
							}
							selection_area_rect.setPosition(cursor_position.x, cursor_position.y);
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							if (elements_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
							{
								add_to_erase_list(elements_on_map[i], &elements_to_erase, i);
								break;
							}
						}
					}
					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					for (int i = 0; i < elements_on_map.size(); ++i)
					{
						if (elements_on_map[i]->disabling_move()) break;
					}

					if (selection_area_is_active)
					{
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							if (selection_area_rect.getGlobalBounds().intersects(elements_on_map[i]->get_rect()))
							{
								reaction_elements_IDs.push_back(elements_on_map[i]->get_id());
								add_to_erase_list(elements_on_map[i], &elements_to_erase, i);
							}
						}
					}
					else
					{
						// OPTIMIZIROVAT ETO VSE, GOSPODI ! ! ! ! ! ! I SMENIT SISTEMY POLNOSTIY
						std::vector<unsigned int> temp_reagents;
						std::vector<unsigned int> temp_erase_list;

						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							bool was_a_reaction = false; // Stopping checks after find the first intersection of rectangles
							for (int j = i+1; j < elements_on_map.size(); ++j)
							{
								if (elements_on_map[i]->check_collision(elements_on_map[j]->get_rect()))
								{
									temp_reagents.push_back(elements_on_map[i]->get_id());
									temp_reagents.push_back(elements_on_map[j]->get_id());
									temp_erase_list.push_back(i);                  
									temp_erase_list.push_back(j);
									std::sort(temp_reagents.begin(), temp_reagents.end());
									for (int f = 0; f < reactions_list.size(); ++f)
									{
										if (reactions_list[f]->check_reaction(temp_reagents, true))
										{
											was_a_reaction = true;
											break;
										}
									}
								}
							}
							
							if (was_a_reaction) 
							{
								for (int m = 0; m < 2; ++m)
								{
									add_to_erase_list(elements_on_map[m], &elements_to_erase, temp_erase_list[m]);
								}
								for (int n = 0; n < 2; ++n)
								{
									reaction_elements_IDs.push_back(temp_reagents[n]);
								}
								break;
							}
							else
							{
								temp_reagents.clear();
								temp_erase_list.clear();
							}
						} // end of I element
					}

					selection_area_is_active = false;
					break;
				}

				case sf::Event::KeyReleased:
				{
					// ++ - VNIZ, -- - VVERX! NAOBOROT!
					if ( (event.key.code == sf::Keyboard::W) ||
						(event.key.code == sf::Keyboard::PageUp) ||
						(event.key.code == sf::Keyboard::Up) )
					{
						if (item_list_page < 0)
						{
							item_list_page++;
						}
					}
					else if ((event.key.code == sf::Keyboard::S) ||
						(event.key.code == sf::Keyboard::PageDown) ||
						(event.key.code == sf::Keyboard::Down) )
					{
						if ( item_list_page*24 < Element::get_open_elements_num() &
							(Element::get_open_elements_num() > 24) )
						{
							item_list_page--;
						}
					}
				}

				default:
				{
					break;
				} // end of default
			} // end of switch
		} // end of while(poolEvent);

		// setting real-time size of selection area
		if (selection_area_is_active)
		{
				// protection against access to the area of opened elements
			float temp_w = cursor_position.x - selection_area_rect.getPosition().x;
			float temp_h = 0;
			if (cursor_position.y > Y_TOP_BORDER_LINE) 
			{
				temp_h = cursor_position.y - selection_area_rect.getPosition().y;
			}
			else
			{
				temp_h = Y_TOP_BORDER_LINE - selection_area_rect.getPosition().y;
			}

			selection_area_rect.setSize(sf::Vector2f(temp_w, temp_h));
		}
		// Check reactions
		if (reaction_elements_IDs.size() > 0)
		{
			std::sort(reaction_elements_IDs.begin(), reaction_elements_IDs.end()); // sort the elements_on_map

			bool was_a_reaction = false;
			for (int i = 0; i < reactions_list.size(); ++i)
			{
				if (reactions_list[i]->check_reaction(reaction_elements_IDs, true))
				{
					elements_to_spawn = reactions_list[i]->get_output_elements();
					was_a_reaction = true;
				}
			}
			reaction_elements_IDs.clear();
			if (!was_a_reaction) elements_to_erase.clear();
		}
		// Removal of elements after the reaction
		if (elements_to_erase.size() > 0)
		{
			for (int i = 0; i < elements_to_erase.size(); ++i)
			{
				elements_on_map.erase(
					elements_on_map.begin() + elements_to_erase[i] - i);
			}
			elements_to_erase.clear();
		}
		// The spawn of new elements
		if (elements_to_spawn.size() > 0)
		{
			float R = 32 * elements_to_spawn.size(); // Radious of sp
			float angle = 0;
			for (int i = 0; i < elements_to_spawn.size(); ++i)
			{
				for (int j = 0, spawn_x, spawn_y; j < elements_list.size(); ++j)
				{
					if (elements_to_spawn[i] == elements_list[j]->get_id())
					{
						spawn_x = cursor_position.x + R*cos(angle) + ELEMENT_DIMENSIONS/2, 
						spawn_y = cursor_position.y + R*sin(angle) + ELEMENT_DIMENSIONS/2;
						angle += 6.28 / elements_to_spawn.size();
						spawn_element(elements_list[j], &elements_on_map, spawn_x, spawn_y);

						break;
					}
				}
			}
			elements_to_spawn.clear();
		}

		window.clear(sf::Color(255, 255, 255));

		int temp_render_element_name_num = -1; // Render the element name
		bool temp_contains = false;
		for (int i = elements_on_map.size()-1; i >= 0; --i)
		{   
			elements_on_map[i]->update(cursor_position);
			elements_on_map[i]->render(window);
			if (!temp_contains)
			{
				if (elements_on_map[i]->rect_contains_cursor(cursor_position.x, cursor_position.y))
				{
					temp_contains = true;
					temp_render_element_name_num = i;
				}
			}
		}

		if (temp_contains) 
		{
			elements_on_map[temp_render_element_name_num]->render_name(window, cursor_position.x, cursor_position.y);
		}

		if (selection_area_is_active) window.draw(selection_area_rect);
		window.draw(element_list_background);
		// int missing_elements - is the number of open items that will not be rendered first. I tried to explain
		for (int i = 0, render_element_number = 0, missing_elements = item_list_page*24, x, y; 
			(i < elements_list.size()) & (render_element_number < 24); 
			++i)
		{
			if (elements_list[i]->is_opened())
			{
				if (missing_elements == 0)
				{
					x = ELEMENT_DIMENSIONS * render_element_number - (WINDOW_W-ELEMENT_DIMENSIONS)*int(render_element_number / 12),
					y = ELEMENT_DIMENSIONS * int(render_element_number/12);
					elements_list[i]->qwerty(x, y);
					elements_list[i]->render(window);
					render_element_number++;
				}
				else
				{
					missing_elements++;
				}
			}
		}

		window.display();
	} // end of while (window.isOpen())

	return 0;
}