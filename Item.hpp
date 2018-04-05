#ifndef ITEM_HPP
#define ITEM_HPP
#include "defines.hpp"

class Item // abstract class
{
protected:
	sf::FloatRect rect;
	int adjustment_x = 0;
	int adjustment_y = 0;
	void check_out_the_field(float *x, float *y);

	sf::String name;
	sf::String description;

	bool is_move_ = false;
	bool is_opened_;
	bool is_static_;

	uint8_t class_; // fire, air ....
	uint8_t item_type; // text_element, timer, counter ....
	unsigned int ID = 0; // 0 == error!

	static sf::FloatRect game_field; // borders the movement of elements on the map. 4to ono tut delaet?

public:
	Item();
	~Item();

	sf::FloatRect get_rect();

	bool toggle_move(); // TURN OFF
	bool toggle_move(sf::Vector2f cursor_position); // TURN ON
	bool is_move();
	bool is_opened();
	unsigned int get_ID();

	sf::String get_name();
	sf::String get_description();

	virtual void update(sf::Vector2f cursor_position, float time) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void set_position(sf::Vector2f coordinates) = 0;
	virtual void set_porition_without_COTF(sf::Vector2f coordinates) = 0;

	static void set_field_rectangle(sf::FloatRect field);
	static sf::FloatRect get_field_rectangle();
};

#endif

/*
google translate power! ^^
Number of element types:
0 - Image_element
1 -
2 -
3 -
ALL THEY INDICATE IN THE CHILD CLASSES!
*/