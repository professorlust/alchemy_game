#include "../../Game.hpp" // Ругаеется, что таких нет

class Charodey : public Game
{
private:
	void initialization_textures();
	void initialization_elements();
	void initialization_reactions();
	void initialization_started_elements();
	
public:
	Charodey();
	~Charodey();	
};