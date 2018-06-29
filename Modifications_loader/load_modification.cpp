#include "Modifications_loader.hpp"

void Modifications_loader::load_modification(std::string file_name, std::vector <sf::Texture*> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy, Game_settings &game_settings)
{
	std::wifstream file(file_name);
	std::wstring process;
	std::vector<Item_color> items_colors;
	std::string images_folder = "";

	unsigned int line = 0;

	// Processing blocks
	uint8_t block = 0;
	enum
	{
		SETTINGS = 1,
		ITEMS,
		REACTIONS,
		COLORS,
		STARTED_ITEMS
	};

	#ifndef WIN32
	std::cout << "On Unix operating systems, modifications may not work correctly!" << std::endl;
	#endif

	if (!file.is_open())
	{
		std::cout << "Load modification error: file not found." << std::endl;
		return;
	}

	while (getline(file, process))
	{
		line++;

		if (process[0] == L'#' ||
			process.size() == 0)
			continue;

		if (process.find(L"ettings:") != std::string::npos)
			block = SETTINGS;
		else if (process.find(L"tarted_elements:") != std::string::npos)
			block = STARTED_ITEMS;
		else if (process.find(L"eactions:") != std::string::npos)
			block = REACTIONS;
		else if (process.find(L"olors:") != std::string::npos)
			block = COLORS;
		else if (process.find(L"ments:") != std::string::npos)
			block = ITEMS;

		else switch (block)
		{
			case SETTINGS:
			{
				remove_spaces(process, true);

				std::wstring setting, value;
				unsigned int i = 0;

				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'#')
						break;

					if (process[i] != L'=')
						setting += process[i];
					else
					{
						i++;
						break;
					}
				}

				for (i; i < process.size(); ++i)
				{
					if (process[i] != L'#')
						value += process[i];
					else
						break;
				}

				if (setting.find(L"name") != std::string::npos)
					game_settings.name = value;

				else if (setting.find(L"author") != std::string::npos)
					game_settings.author = value;

				else if (setting.find(L"description") != std::string::npos)
					game_settings.description = value;

				else if (setting.find(L"render_top_elements_panel") != std::string::npos)
					game_settings.render_top_elements_panel = (value.find(L"rue") != std::string::npos) || (value.find(L"1") != std::string::npos);

				else if (setting.find(L"deletion_elements_RMB") != std::string::npos)
					game_settings.deletion_elements_RMB = (value.find(L"rue") != std::string::npos) || (value.find(L"1") != std::string::npos);

				else if (setting.find(L"images_folder") != std::string::npos)
					images_folder = std::string(value.begin(), value.end());

				break;
			}

			case COLORS:
			{
				remove_spaces(process);

				unsigned int i = 1; // process[0] == "
				items_colors.push_back(Item_color());
				items_colors.back().name.clear();

				/* Getting color name */
				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'"' ||
						process[i] == L'\'')
					{
						i++;
						break;
					}

					items_colors.back().name += process[i];
				}

				/* Getting color text and background */
				for (uint8_t s = 0; s < 2; ++s)
				{
					std::wstring argument, value;

					for (i; i < process.size(); ++i)
					{
						if (process[i] == L'(')
						{
							i++;
							break;
						}

						argument += process[i];
					}

					for (i; i < process.size(); ++i)
					{
						if (process[i] == L')')
						{
							i++;
							break;
						}

						value += process[i];
					}

					sf::Color load_color;
					std::wstring temp = L"0"; // Protection against errors

					/* Getting color R G B data */
					for (int s = 0, step = 0; s < value.size(); ++s)
					{
						if (value[s] == L',' ||
							s == value.size()-1)
						{
							if (s == value.size()-1)
								temp += value[s];

							if (step == 0)
								load_color.r = std::stoi(temp);
							else if (step == 1)
								load_color.g = std::stoi(temp);
							else if (step == 2)
								load_color.b = std::stoi(temp);
							else
								break;

							step++;
							temp = L"0";
							continue;
						}

						temp += value[s];
					}

					if (argument.find(L"text") != std::string::npos)
						items_colors.back().text = load_color;
					if (argument.find(L"background") != std::string::npos)
						items_colors.back().background = load_color;
				}

				break;
			}

			case ITEMS:
			{
				enum
				{
					ELEMENT = 0,
					TIMER,
					COUNTER,
					NOT_FOUND
				};

				unsigned int i = 0;
				bool comment_block = false;
				std::wstring buffer;

				/* Getting item type */
				int8_t type = -1;
				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'#')
					{
						comment_block = true;
						break;
					}
					else if (process[i] == L' ')
					{
						i++;
						break;
					}

					buffer += process[i];
				}

				if (comment_block)
					break;

				if (buffer.find(L"element") != std::string::npos)
					type = ELEMENT;
				else if (buffer.find(L"timer") != std::string::npos)
					type = TIMER;
				else if (buffer.find(L"counter") != std::string::npos)
					type = COUNTER;
				else
					break;

				/* Skipping unnecessary spaces */
				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'#')
					{
						comment_block = true;
						break;
					}
					else if (process[i] == L'"')
					{
						i++;
						break;
					}
				}

				if (comment_block)
					break;

				/* Getting item name */
				std::wstring name;
				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'#')
					{
						comment_block = true;
						break;
					}
					else if (process[i] == L'"')
					{
						i += 2; // skip quotes and space
						break;
					}

					name += process[i];
				}

				if (comment_block)
					break;

				/* Getting item additional parameters */
				buffer.clear();
				bool in_quotes = false;

				bool is_static = false;
				bool has_image = false;
				std::wstring description;
				Item_color color;

				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'#')
						break;

					if (process[i] == L'(' ||
						process[i] == ')')
						in_quotes = !in_quotes;

					// Getting a separate argument
					if ( (process[i] == L' ' || i == process.size()-1) &&
						!in_quotes)
					{
						if (i == process.size()-1)
							buffer += process[i];

						std::wstring argument, value;
						bool trigger = false; // 0 - argument, 1 - value
						for (auto & j : buffer)
						{
							if (j == L'(')
							{
								trigger = true;
								continue;
							}
							else if (j == L')')
							{
								trigger = true;
								continue;
							}

							if (j == L'"')
								continue;

							if (j == L'#')
							{
								comment_block = true;
								break;
							}

							(trigger) ? value += j : argument += j;
						}

						if (comment_block)
							break;

						if (argument.find(L"is_static") != std::string::npos)
							is_static = true;
						else if (argument.find(L"image") != std::string::npos)
						{
							item_textures_copy.push_back(new sf::Texture());
							item_textures_copy.back()->loadFromFile(CONFIG.modifications_folder() + '/' + images_folder + '/' + std::string(value.begin(), value.end()));
							has_image = true;
						}
						else if (argument.find(L"description") != std::string::npos)
							description = value;
						else if (argument.find(L"color") != std::string::npos)
						{
							if (value.find(L"Air") != std::string::npos)
								color = AIR_COLOR;
							else if (value.find(L"Fire") != std::string::npos)
								color = FIRE_COLOR;
							else if (value.find(L"Earth") != std::string::npos)
								color = EARTH_COLOR;
							else if (value.find(L"Water") != std::string::npos)
								color = WATER_COLOR;
							else if (value.find(L"Light green") != std::string::npos)
								color = LIGHT_GREEN_COLOR;
							else if (value.find(L"Purple") != std::string::npos)
								color = PURPLE_COLOR;
							else if (value.find(L"Grey") != std::string::npos)
								color = GREY_COLOR;
							else if (value.find(L"Light pink") != std::string::npos)
								color = LIGHT_PINK_COLOR;
							else if (value.find(L"Dark") != std::string::npos)
								color = DARK_COLOR;
							else if (value.find(L"Dark blue") != std::string::npos)
								color = DARK_RED_COLOR;
							else if (value.find(L"Orange") != std::string::npos)
								color = ORANGE_COLOR;
							else if (value.find(L"Dark green") != std::string::npos)
								color = DARK_GREEN_COLOR;
							else
							{
								for (int j = 0; j < items_colors.size(); ++j)
								{
									if (items_colors[j].name.toWideString() == value)
									{
										color = items_colors[j];
										break;
									}
								}
							}
						}

						argument.clear();
						value.clear();
						buffer.clear();
						trigger = false;
						continue;
					}

					buffer += process[i];
				}

				if (type == ELEMENT)
				{
					if (has_image)
						items_list_copy.emplace_back(item_textures_copy.back(), name, description, items_list_copy.size()+1, is_static);
					else
						items_list_copy.emplace_back(name, description, items_list_copy.size()+1, color, is_static);
				}
				break;
			}

			case REACTIONS:
			{
				remove_spaces(process, true);

				unsigned int i = 0;
				bool input_block = true, input_block_trigger = false;

				std::wstring reagent_buffer;

				std::vector<unsigned int> input;
				std::vector<Reagent> output;

				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'+' ||
						process[i] == L'=' ||
						i == process.size()-1)
					{
						if (i == process.size()-1)
							reagent_buffer += process[i];

						// getting argumens
						unsigned int j = 0;
						std::wstring reagent_name, value;

						if (process[i] == L'=')
							input_block_trigger = true;

						for (j; j < reagent_buffer.size(); j++)
						{
							if (reagent_buffer[j] == L'[')
							{
								j++;
								break;
							}

							reagent_name += reagent_buffer[j];
						}

						for (j; j < reagent_buffer.size(); j++)
						{
							if (reagent_buffer[j] == L']')
							{
								j++;
								break;
							}

							value += reagent_buffer[j];
						}

						if (!input_block)
						{
							output.push_back(Reagent{get_item_id_by_name(reagent_name, items_list_copy)});

							if (value.find(L"random") != std::string::npos)
							{
								bool trigger = false;
								std::wstring int_wstr = L"0";

								for (auto & c : value)
								{
									if (c == L'(' ||
										c == L')')
									{
										trigger = true;
										continue;
									}

									if (trigger)
										int_wstr += c;
								}

								output.back().chance = std::stof(int_wstr)*100;

								if (output.back().chance > 10000)
									output.back().chance = 10000;
							}

							else if (value.find(L"delete") != std::string::npos)
								output.back().remove = true;

							// This may not work correctly on Linux operating systems. More precisely, the chances are higher than usual
							else if (value[0] == L'?' ||
									 value[0] == L'!' ||
									 value[0] == L'<' ||
									 value[0] == L'>' ||
									 value[0] == L'*' ||
									 value[0] == L'-')
							{
								std::set<char16_t> conditions_symbols = { L'?', L'!', L'>', L'<', L'~', L'*', L'-' };

								enum
								{
									ITEM_ON_MAP = 0, // ?
									ITEM_NOT_ON_MAP, // !
									COUNTER_MORE,    // >
									COUNTER_LESS,    // <
									COUNTER_IS,      // ~
									ITEM_IS_OPEN,    // *
									ITEM_IS_CLOSE    // -
								};

								auto get_condition_id = [](char16_t s) -> uint8_t const
								{
									if (s == L'?')
										return ITEM_ON_MAP;

									else if (s == L'!')
										return ITEM_NOT_ON_MAP;

									else if (s == L'>') // Coming soon
										return COUNTER_MORE;

									else if (s == L'<') // Coming soon
										return COUNTER_LESS;

									else if (s == L'~') // Coming soon
										return COUNTER_IS;

									else if (s == L'*')
										return ITEM_IS_OPEN;

									else if (s == L'-')
										return ITEM_IS_CLOSE;

									return 255;
								};
								uint8_t condition_id;

								std::wstring item_name;

								for (unsigned int i = 0; i < value.size(); ++i)
								{
									if (conditions_symbols.count(value[i]) ||
										i == value.size()-1)
									{
										if (i == value.size()-1 &&
											!conditions_symbols.count(value[i]))
											item_name += value[i];

										if (!item_name.empty())
											switch (condition_id)
										{
											case ITEM_ON_MAP:
											{
												unsigned int id = get_item_id_by_name(item_name, items_list_copy);
												output.back().found_on_map.push_back(id);

												break;
											}

											case ITEM_NOT_ON_MAP:
											{
												unsigned int id = get_item_id_by_name(item_name, items_list_copy);
												output.back().not_found_on_map.push_back(id);

												break;
											}

											case COUNTER_MORE:
											{
												break;
											}

											case COUNTER_LESS:
											{
												break;
											}

											case COUNTER_IS:
											{
												break;
											}

											case ITEM_IS_OPEN:
											{
												unsigned int id = get_item_id_by_name(item_name, items_list_copy);
												output.back().items_is_open.push_back(id);

												break;
											}

											case ITEM_IS_CLOSE:
											{
												unsigned int id = get_item_id_by_name(item_name, items_list_copy);
												output.back().items_is_not_open.push_back(id);

												break;
											}

											default:
												break;
										}

										condition_id = get_condition_id(value[i]);
										item_name.clear();
										continue;
									}
									item_name += value[i];
								}
							}

						}
						else
							input.push_back(get_item_id_by_name(reagent_name, items_list_copy));

						if (input_block_trigger)
							input_block = false;

						reagent_buffer.clear();
						continue;
					}

					reagent_buffer += process[i];
				}

				std::sort(input.begin(), input.end());
				reactions_list_copy.push_back(Reaction(input, output));

				break;
			}

			case STARTED_ITEMS:
			{
				for (auto & i : items_list_copy)
				{
					if (i.get_name().toWideString() == process)
					{
						started_items_copy.push_back(Reagent({i.get_id()}));
						break;
					}
				}
			}

			default:
				break;
		}
	}

	file.close();
}