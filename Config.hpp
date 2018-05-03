#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <string>

class Config
{
public:
	Config(std::string file);
	~Config();	
};

#endif