#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "defines.hpp"

class Config
{
private:
	std::ifstream file;

	void load_from_file();
	void create_new_config_ini();

	bool autosave_ = false;
	float autosave_timer_ = 0; // Value in seconds

	std::string modifications_folder_;

public:
	Config();
	~Config();

	/* Methods for obtaining data. All methods are CONST */
	bool autosave() const;
	float autosave_timer() const;
	std::string modifications_folder() const;
};

const Config CONFIG;

#endif