#ifndef MODIFICATIONS_LOADER
#define MODIFICATIONS_LOADER

#include "Game.hpp"
#include "Config.hpp"

class Modifications_loader : public Game
{
private:
	std::string file_name;
	std::string process; // Kostyl, kotoryy nuzhen dlya vozmozhnosti obrabotki strok
	std::string modification_image_folder_name;

	bool load_game_data_from_file();
	std::vector<Item_color> item_colors;

	/* Virtual methods reinitialize */
	// In this class they only process lines.
	// This methods process the string "process"
	void initialization_textures();
	void initialization_items();
	void initialization_reactions();
	void initialization_started_items();
	void initialization_settings();

	void initialization_colors(); // only for Modifications_loader
	void removing_spaces(); // removing spaces from process string

	static const char comment_flag = '#';

public:
	Modifications_loader(std::string file);
	~Modifications_loader();

	static void create_modification_template();
};
#endif