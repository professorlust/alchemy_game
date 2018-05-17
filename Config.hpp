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

public:
	Config(std::string file_p);
	~Config();	
};

#endif