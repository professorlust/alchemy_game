#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <string>
#include "defines.hpp"
#include <iostream>

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