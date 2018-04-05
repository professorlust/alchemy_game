#include "Item.hpp"

Item::Item() {}

Item::~Item() {}

void Item::check_out_the_field(float *x, float *y)
{
	int Y_TOP_BORDER_LINE = game_field.top,
	Y_BOTTOM_BORDER_LINE = game_field.top + game_field.height,
	X_LEFT_BORDER_LINE = game_field.left,
	X_RIGHT_BORDER_LINE = game_field.left + game_field.width;

	if (*y < Y_TOP_BORDER_LINE) *y = Y_TOP_BORDER_LINE;
	if (*y > Y_BOTTOM_BORDER_LINE - ELEMENT_DIMENSIONS) *y = Y_BOTTOM_BORDER_LINE - rect.height;
	if (*x < X_LEFT_BORDER_LINE) *x = X_LEFT_BORDER_LINE;
	if (*x > X_RIGHT_BORDER_LINE - ELEMENT_DIMENSIONS) *x = X_RIGHT_BORDER_LINE - rect.width;
}

sf::FloatRect Item::get_rect()
{
	return rect;
}

sf::String Item::get_name()
{
	return name;
}

sf::String Item::get_description()
{
	return description;
}

bool Item::toggle_move() // TURN OFF
{
	if (is_move_)
	{
 		is_move_ = false;
 		return true;
 	}
 	else return false;
}

bool Item::toggle_move(sf::Vector2f cursor_position) // TURN ON
{
	if (!is_move_)
	{
		adjustment_x = cursor_position.x - rect.left;
		adjustment_y = cursor_position.y - rect.top;
		is_move_ = true;
		return true;
	}
	else return false;
}

bool Item::is_move()
{
	return is_move_;
}

bool Item::is_opened()
{
	return is_opened_;
}

unsigned int Item::get_ID()
{
	return ID;
}
// STATIC /////////////////////

void Item::set_field_rectangle(sf::FloatRect field)
{
	game_field = field;
}

sf::FloatRect Item::get_field_rectangle()
{
	return game_field;
}

sf::FloatRect Item::game_field = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H);