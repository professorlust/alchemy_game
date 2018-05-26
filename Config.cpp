#include "Config.hpp"

Config::Config()
{
	// WINDOW_H and WINDOW_W in defines.cpp
	file.open("config.ini");

	if (!file.is_open())
	{
		create_new_config_ini();
		std::cout << "config.ini not found. Creating a new file. Standard values are set in the file." << std::endl;
	}

	load_from_file();
	file.close();
}

Config::~Config()
{

}

void Config::create_new_config_ini()
{
	std::ofstream config_file("config.ini");

	config_file
		<< "width = 800" << std::endl
		<< "height = 600" << std::endl
		<< "font = lucon.ttf" << std::endl
		<< std::endl
		<< "autosave = true" << std::endl
		<< "autosave_timer = 180 // Value in seconds. Can not be less than 60" << std::endl;
}

void Config::load_from_file()
{
	bool font_loaded = false,
	width_loaded = false,
	height_loaded = false;

	std::string buffer;
	while (std::getline(file, buffer))
	{
		if (buffer.size() == 0 || // Skipping empty lines
			buffer[0] == '#')
			continue;

		std::string argument, operator_, value;

		for (int i = 0, step = 0; i < buffer.size(); ++i)
		{
			if (buffer[i] == '#') // Beginning of comments block
				break;

			if (step == 0)
			{
				if (buffer[i] != ' ')
					argument += buffer[i];
				else
					step++;
			}
			else if (step == 1)
			{
				if (buffer[i] != ' ')
					operator_ += buffer[i];
				else
					step++;
			}
			else // if step == 2
			{
				value += buffer[i];
			}
		}

		/* Global variables reinitialization */
		if (argument == "font" && !font_loaded)
		{
			if (!GLOBAL_FONT.loadFromFile(value)) // Protection against missing font
				GLOBAL_FONT.loadFromFile("lucon.ttf");
			font_loaded = true;
		}
		else if (argument == "width" && !width_loaded)
		{
			int window_w = atoi(value.c_str());
			WINDOW_W = std::max(64, window_w);

			width_loaded = true;
		}
		else if (argument == "height" && !height_loaded)
		{
			int window_h = atoi(value.c_str());
			WINDOW_H = std::max(ITEM_DIMENSIONS*3, window_h);

			height_loaded = true;
		}

		/* Autosave settings */
		else if (argument == "autosave")
		{
			if (value == "true" || value == "false") // The verbal value is entered
				(value == "true") ? autosave_ = true : autosave_ = false;
			else // Numeric value entered
				autosave_ = atoi(value.c_str());
		}

		else if (argument == "autosave_timer")
		{
			autosave_timer_ = atoi(value.c_str());
			if (autosave_timer_ < 60)
				autosave_timer_ = 60;
		}
	}
}

bool Config::autosave() const
{
	return autosave_;
}

float Config::autosave_timer() const
{
	return autosave_timer_;
}