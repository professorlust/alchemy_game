#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

class Config
{
private:
	std::ifstream file;

	bool autosave_ = false;
	float autosave_timer_ = 0; // Value in seconds

	std::string modifications_folder_ = "modifications";
	std::string font_name_ = "lucon.ttf";

	void load_from_file();
	void create_new_config_ini() const;

	sf::Vector2u w_sizes = sf::Vector2u(800, 600);
	unsigned int i_side = 64;

	unsigned int max_FPS = 60;

public:
	Config();
	~Config();

	/* Methods for obtaining data. All methods are CONST */
	bool autosave() const;
	float autosave_timer() const;
	std::string modifications_folder() const;
	sf::Vector2u window_sizes() const;
	unsigned int item_side() const;
	std::string font_name() const;
	unsigned int fps_limit() const;

	/* Static methods */
	static sf::FloatRect borders;
	static void set_borders(sf::FloatRect rect);
	static sf::Font font;
};

extern const Config CONFIG;

#endif