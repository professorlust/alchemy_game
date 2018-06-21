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
						items_colors[items_colors.size()-1].text = load_color;
					if (argument.find(L"background") != std::string::npos)
						items_colors[items_colors.size()-1].background = load_color;
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
				unsigned int color = 0;

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
						for (unsigned int j = 0; j < buffer.size()-1; ++j)
						{
							if (buffer[j] == '(')
							{
								trigger = true;
								continue;
							}

							if (buffer[j] == '#')
							{
								comment_block = true;
								break;
							}

							(trigger) ? value += buffer[j] : argument += buffer[j];
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
							for (int j = 0; j < items_colors.size(); ++j)
							{
								if (items_colors[j].name.toWideString() == value)
								{
									color = j;
									break;
								}
							}
						}

						buffer.clear();
						continue;
					}

					buffer += process[i];
				}

				if (type == ELEMENT)
				{
					if (has_image)
						items_list_copy.emplace_back(item_textures_copy.back(), name, description, items_list_copy.size()+1);
					else
						items_list_copy.emplace_back(name, description, items_list_copy.size()+1, items_colors[color]);
				}
				break;
			}

			case REACTIONS:
			{
				remove_spaces(process, true);

				unsigned int i = 0;
				bool input_block = true;

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

						// reagent_buffer block! =============
						unsigned int j = 0;
						std::wstring argument, value;

						std::wcout << "reagent_buffer: " << reagent_buffer << std::endl
						<< "Argument: " << argument << std::endl
						<< "Value: " << value << std::endl << std::endl;

						if (process[i] == L'=')
							input_block = false;
						// reagent_buffer block! =============
						
						reagent_buffer.clear();
						continue;
					}

					reagent_buffer += process[i];
				}

				reactions_list_copy.push_back(Reaction(input, output));
				break;
			}

			default:
				break;
		}
	}

	// debug
	// std::cout << game_settings.name.toAnsiString() << std::endl
	// << game_settings.author.toAnsiString() << std::endl
	// << game_settings.description.toAnsiString() << std::endl
	// << std::endl
	// << "Item colors:" << std::endl;
	// for (auto & i : items_colors)
	// 	std::cout << i.name.toAnsiString()
	// 	<< " text(" << int(i.text.r) << " " << int(i.text.g) << " " << int(i.text.b)
	// 	<< ") background(" << int(i.background.r) << " " << int(i.background.g) << " " << int(i.background.b) << ")" << std::endl;
}