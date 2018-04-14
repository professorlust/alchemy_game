#include "../../Game.hpp"

class Test_game : public Game
{
private:
	void initialization_textures();
	void initialization_elements();
	void initialization_reactions();
	void initialization_started_elements();
	
public:
	Test_game();
	~Test_game();	
};