#include "Config.hpp"

Config::Config()
{
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
		<< "FPS_limit = 60" << std::endl
		<< std::endl
		<< "autosave = true" << std::endl
		<< "autosave_timer = 180 # Value in seconds. Can not be less than 60" << std::endl
		<< std::endl
		<< "modifications_folder = modifications" << std::endl
		<< "font = lucon.ttf" << std::endl;
}

void Config::load_from_file()
{
	std::string buffer;
	while (std::getline(file, buffer))
	{
		if (buffer.size() == 0 || // Skipping empty lines
			buffer[0] == '#')
			continue;

		std::string argument, value;

		unsigned int symbol = 0;
		while (symbol < buffer.size())
		{
			if (buffer[symbol] == ' ')
				buffer.erase(buffer.begin()+symbol);
			else
				symbol++;
		}

		bool trigger = false; // 0 - argument, 1 - value
		for (auto i = 0; i < buffer.size() && buffer[i] != '#'; ++i)
		{
			if (buffer[i] == '=')
			{
				trigger = true;
				continue;
			}

			if (buffer[i] == '#')
				break;

			(trigger) ? value += buffer[i] : argument += buffer[i];
		}

		/* Global variables reinitialization */
		if (argument == "font")
			font_name_ = value;
		else if (argument == "width")
		{
			int window_w = atoi(value.c_str());
			w_sizes.x = std::max(64, window_w);
		}
		else if (argument == "height")
		{
			unsigned int window_h = atoi(value.c_str());
			w_sizes.y = std::max(i_side*3, window_h);
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

		/* Other */
		else if (argument == "modifications_folder")
			modifications_folder_ = value;
		else if (argument == "FPS_limit")
			max_FPS = atoi(value.c_str());

		buffer.clear();
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

std::string Config::modifications_folder() const
{
	return modifications_folder_;
}

sf::Vector2u Config::window_sizes() const
{
	return w_sizes;
}

unsigned int Config::item_side() const
{
	return i_side;
}

std::string Config::font_name() const
{
	return font_name_;
}

unsigned int Config::fps_limit() const
{
	return max_FPS;
}

/* Statics */
const Config CONFIG;
sf::FloatRect Config::borders = sf::FloatRect(0, CONFIG.item_side()*2, CONFIG.window_sizes().x, CONFIG.window_sizes().y - CONFIG.item_side()*2);
sf::Font Config::font = sf::Font();