#include <iostream>
#include <vector>
#include "defines.hpp"
#include "main.hpp"

int main(int argc, char const *argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H, 32), "AlchemyGame", sf::Style::Close);
	window.setFramerateLimit(30);
	Item::set_field_rectangle(sf::FloatRect(0, ELEMENT_DIMENSIONS*2, WINDOW_W, WINDOW_H-ELEMENT_DIMENSIONS*2));

	sf::Clock clock; // World clock
	float time = 0; // Time cash
	float FPS = 0; // Frames per second

	sf::RectangleShape selection_area_rect; // The selection area when the left button is pressed
	selection_area_rect.setPosition(-1, -1);
	selection_area_rect.setFillColor(sf::Color(0, 0, 150, 150)); // Light blue
	selection_area_rect.setSize(sf::Vector2f(1, 1));
	bool selection_area_is_active = false;

	sf::Vector2f cursor_position; // Cursor coordinates

	sf::Texture texture;
	texture.loadFromFile("standart_games_sp/charodey/fire.png");

	sf::Texture texture1;
	texture1.loadFromFile("standart_games_sp/charodey/air.png");

	std::vector<Item*> list_of_elements; // All lists is loaded from the Game*
	std::vector<Item*> elements_on_map;
	std::vector<Reaction*> reactions_list; 
	std::vector<unsigned int> reaction_elements_IDs; // IDs of the elements that react in this frame
	std::vector<unsigned int> elements_to_erase; // Positions of the elements in the array elements_on_map to be deleted
	std::vector<unsigned int> elements_to_spawn; // IDs of the elemenets that will spawn after reaction
	std::vector<sf::Texture*> textures; // Used when downloading a game from a file

	list_of_elements.push_back(new Image_item(&texture, "Fire", "", 1, sf::Vector2f(50, 50), 1, 1));
	list_of_elements.push_back(new Image_item(&texture1, "Fire", "", 2, sf::Vector2f(50, 50), 1, 1));

	reactions_list.push_back(new Reaction({1, 2}, {1, 2}));

/*//////////////////////// Саня-тян
	Image_item item1(&texture, "Fire", "", 1, sf::Vector2f(50, 50), 1, 1); // Просто объект класса картинкоэлемента
	Image_item item2(item1, sf::Vector2f(0,0)); // Копируем просто картинкоэлемент - все окей.
	Item* item3 = new Image_item(&texture, "Fire", "", 1, sf::Vector2f(50, 50), 1, 1); // Апкаст
	Item* item4 - new Image_item(?); item3. Как это сделать конструктором копирования? Он должен принимать именно Item, 
											а не Image_item и копировать все, включая переменные только из картинкоэле-
											мента (текстура, спрайт)
*///////////////////////////

	while (window.isOpen())
	{
		cursor_position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Getting cursor position
		time = clock.getElapsedTime().asSeconds(); // Getting time
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
						if (cursor_position.y < Item::get_field_rectangle().top) // hit elements panel
						{
							for (int i = 0; i < list_of_elements.size(); ++i)
							{
								/* code */
							}
						}
						else // Hit any point in game zone
						{
							selection_area_is_active = true;
							selection_area_rect.setPosition(cursor_position.x, cursor_position.y);

							for (int i = 0; i < elements_on_map.size(); ++i)
							{
								if (elements_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
								{
									selection_area_is_active = false;
									elements_on_map[i]->toggle_move(cursor_position);
									break;
								}
							}
						}
					}

					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							if (elements_on_map[i]->get_rect().contains(cursor_position.x, cursor_position.y))
							{
								elements_to_erase.push_back(i);
								break;
							}
						}
					}
					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					if (selection_area_is_active)
					{
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							if (selection_area_rect.getGlobalBounds().intersects(elements_on_map[i]->get_rect()))
							{
								reaction_elements_IDs.push_back(elements_on_map[i]->get_ID());
								elements_to_erase.push_back(i);
							}
						}
					}
					else
					{
						/* TOGGLE MOVE TO OFF */
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							if (elements_on_map[i]->is_move())
							{
								elements_on_map[i]->toggle_move();
								break;
							}
						}

						/* CHECK REACTIONS */
						std::vector<unsigned int> temp_reagents;
						std::vector<unsigned int> temp_erase_list;
						bool was_a_reaction = false;
						for (int i = 0; i < elements_on_map.size(); ++i)
						{
							for (int j = i+1; j < elements_on_map.size(); ++j)
							{
								bool intersects = elements_on_map[i]->get_rect().intersects(elements_on_map[j]->get_rect());
								if ( (i != j) & (intersects) )
								{
									temp_reagents.push_back(elements_on_map[i]->get_ID());
									temp_reagents.push_back(elements_on_map[j]->get_ID());
									temp_erase_list.push_back(i);                  
									temp_erase_list.push_back(j);
									std::sort(temp_reagents.begin(), temp_reagents.end());

									for (int f = 0; f < reactions_list.size(); ++f)
									{
										if (reactions_list[f]->check_reaction(temp_reagents))
										{
											elements_to_spawn = reactions_list[f]->get_output_reagents();
											was_a_reaction = true;
											break;
										}
									}
								}

								if (was_a_reaction)
								{
									break;
								}
							}

							if (was_a_reaction)
							{
								break;
							}
						}

						if (was_a_reaction) 
						{
							elements_to_erase = temp_erase_list;
							break;
						}
						else
						{
							temp_reagents.clear();
							temp_erase_list.clear();
						}
					}

					selection_area_is_active = false;
					break; // case out
				}

				default: 
				{ 
					break; 
				}
			}
		} // end of while (window.pollEvent(event))

		/* Updating the condition of items */
		for (int i = 0; i < elements_on_map.size(); ++i)
		{
			elements_on_map[i]->update(cursor_position, time);
			/* ОБРАБОТКА ОБЪЕКТНЫХ ЭЛЕМЕНТОВ БУДЕТ ТУТ */
		}

		/* Deleting items that are in the deletion queue */
		if (elements_to_erase.size() > 0)
		{
			for (int i = 0; i < elements_to_erase.size(); ++i)
			{
				elements_on_map.erase(elements_on_map.begin() + elements_to_erase[i] - i);
			}
			elements_to_erase.clear();
		}

		/* Spawning new elements */
		if (elements_to_spawn.size() > 0)
		{
			for (int i = 0; i < elements_to_spawn.size(); ++i)
			{
				for (int j = 0; j < list_of_elements.size(); ++j)
				{
					if (elements_to_spawn[i] == list_of_elements[j]->get_ID())
					{
						//elements_on_map.push_back(new Image_item(list_of_elements[j], sf::Vector2f(i*100, i*75)));
					}
				}
			}
			elements_to_spawn.clear();
		}

		/* Update selection area */
		if (selection_area_is_active)
		{
			// protection against access to the area of opened elements
			float temp_w = cursor_position.x - selection_area_rect.getPosition().x;
			float temp_h = 0;
			if (cursor_position.y > Item::get_field_rectangle().top) 
			{
				temp_h = cursor_position.y - selection_area_rect.getPosition().y;
			}
			else
			{
				temp_h = Item::get_field_rectangle().top - selection_area_rect.getPosition().y;
			}

			selection_area_rect.setSize(sf::Vector2f(temp_w, temp_h));
		}
		
		window.clear(sf::Color(255, 255, 255));
		for (int i = elements_on_map.size()-1; i >= 0; --i)
		{
			elements_on_map[i]->render(window);
		}

		if (selection_area_is_active) 
		{
			window.draw(selection_area_rect);
		}

		window.display();
	} // end of while (window.isOpen())

	return 0;
}