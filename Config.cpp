#include "Config.hpp"

Config::Config(std::string file_p)
{
	// WINDOW_H and WINDOW_W in defines.cpp
	file.open(file_p);
	if (file.is_open())
		load_from_file();
	file.close();
}

Config::~Config()
{

}

void Config::load_from_file()
{
	std::string buffer;

	bool font_loaded = false,
	width_loaded = false,
	height_loaded = false;

	while (std::getline(file, buffer))
	{
		std::string argument, operator_, value;

		for (int i = 0, step = 0; i < buffer.size(); ++i)
		{
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
				value += buffer[i];
		}

		if (argument == "font" & !font_loaded)
		{
			if (!GLOBAL_FONT.loadFromFile(value)) // Protection against missing font
				GLOBAL_FONT.loadFromFile("lucon.ttf"); 
			font_loaded = true;
		}
		else if (argument == "width" & !width_loaded)
		{
			int window_w = atoi(value.c_str());
			WINDOW_W = std::max(64, window_w);

			width_loaded = true;
		}
		else if (argument == "height" & !height_loaded)
		{
			int window_h = atoi(value.c_str());
			WINDOW_H = std::max(ITEM_DIMENSIONS*3, window_h);

			height_loaded = true;
		}
	}
}
