#include "../../Game.hpp"

class Charodey : public Game
{
private:
	void initialization_textures();
	void initialization_items();
	void initialization_reactions();
	void initialization_started_items();
	void initialization_settings();
	
public:
	Charodey();
	~Charodey();	
};