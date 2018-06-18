#include "Modifications_loader.hpp"

void Modifications_loader::load_modification(std::string file_name, std::vector <sf::Texture> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy, Game_settings &game_settings)
{
	std::wifstream file(file_name);
	std::wstring process;
	std::vector<Item_color> items_colors;

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

				break;
			}

			case COLORS:
			{
				remove_spaces(process);

				unsigned int i = 1; // process[0] == "
				items_colors.push_back(Item_color());
				items_colors[items_colors.size()-1].name.clear();

				for (i; i < process.size(); ++i)
				{
					if (process[i] == L'"' ||
						process[i] == L'\'')
					{
						i++;
						break;
					}

					items_colors[items_colors.size()-1].name += process[i];
				}

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
					std::wcout << value << std::endl;
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
					COUNTER
				};

				break;
			}

			default:
				break;
		}
	}

	// debug
	std::cout << game_settings.name.toAnsiString() << std::endl
	<< game_settings.author.toAnsiString() << std::endl
	<< game_settings.description.toAnsiString() << std::endl
	<< std::endl
	<< "Item colors:" << std::endl;
	for (auto & i : items_colors)
		std::cout << i.name.toAnsiString()
		<< " text(" << int(i.text.r) << " " << int(i.text.g) << " " << int(i.text.b)
		<< ") background(" << int(i.background.r) << " " << int(i.background.g) << " " << int(i.background.b) << ")" << std::endl;
}