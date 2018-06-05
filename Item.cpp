#include "Item.hpp"

Item::Item(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, const Item_color item_color_, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);
	has_image_ = true;

	rect.left = rect.top = 0;
	rect.height = rect.width = CONFIG.item_side();

	item_color = item_color_;

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;
}

Item::Item(sf::String name, sf::String description, unsigned int ID, const Item_color item_color_, bool is_static)
{
	has_image_ = false;

	rect.left = rect.top = 0;
	rect.width = name.getSize()*10;
	rect.height = 16;

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;

	item_color = item_color_;

	background.setFillColor(item_color.background);
	background.setSize(sf::Vector2f(name.getSize()*10, 16));

	text_name.setCharacterSize(16);
	text_name.setFillColor(item_color.text);
	text_name.setFont(Config::font);
	text_name.setString(name);
}

Item::Item(const Item &copy, sf::Vector2f coordinates)
{
	if (this != &copy)
	{
		has_image_ = copy.has_image_;
		if (has_image_)
		{
			texture = copy.texture;
			sprite.setTexture(*texture);
		}

		name = copy.name;
		ID = copy.ID;
		is_opened_ = false;
		is_static_ = copy.is_static_;
		description = copy.description;

		rect.width = copy.rect.width;
		rect.height = copy.rect.height;
		set_position(coordinates);

		item_color = copy.item_color;

		background.setFillColor(item_color.background);
		background.setSize(sf::Vector2f(name.getSize()*10, 16));

		text_name.setCharacterSize(16);
		text_name.setFillColor(item_color.text);
		text_name.setFont(Config::font);
		text_name.setString(name);
	}
}

Item::~Item()
{

}

/* General methods */

void Item::update(sf::Vector2f coordinates, float time)
{
	if (is_move)
	{
		float new_x = coordinates.x - adjustment_x,
		      new_y = coordinates.y - adjustment_y;
		check_out_the_field(&new_x, &new_y);
		rect.left = new_x;
		rect.top = new_y;
		if (has_image_)
			sprite.setPosition(rect.left, rect.top);
		else
		{
			background.setPosition(rect.left, rect.top);
			text_name.setPosition(rect.left, rect.top);
		}
	}
}

void Item::render(sf::RenderWindow &window)
{
	if (has_image_)
		window.draw(sprite);
	else
	{
		window.draw(background);
		window.draw(text_name);
	}
}

bool Item::toggle_move() // to OFF
{
	if (is_move)
	{
 		is_move = false;
 		return true;
 	}

	return false;
}

bool Item::toggle_move(sf::Vector2f cursor_position) // to ON
{
	if (!is_move)
	{
		adjustment_x = cursor_position.x - rect.left;
		adjustment_y = cursor_position.y - rect.top;
		is_move = true;
		return true;
	}

	return false;
}

void Item::check_out_the_field(float *x, float *y) const
{
	int y_top_border = Config::borders.top,
	y_bottom_border = Config::borders.top + Config::borders.height,
	x_left_border = Config::borders.left,
	x_right_border = Config::borders.left + Config::borders.width;

	if (*y < y_top_border) *y = y_top_border;
	if (*y > y_bottom_border - CONFIG.item_side()) *y = y_bottom_border - rect.height;
	if (*x < x_left_border) *x = x_left_border;
	if (*x > x_right_border - CONFIG.item_side()) *x = x_right_border - rect.width;
}

/* Methods for setting data */

void Item::set_position(sf::Vector2f coordinates)
{
	check_out_the_field(&coordinates.x, &coordinates.y);
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image_)
		sprite.setPosition(rect.left, rect.top);
	else
	{
		background.setPosition(rect.left, rect.top);
		text_name.setPosition(rect.left, rect.top);
	}
}

void Item::set_position_hard(sf::Vector2f coordinates)
{
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image_)
		sprite.setPosition(rect.left, rect.top);
	else
	{
		background.setPosition(rect.left, rect.top);
		text_name.setPosition(rect.left, rect.top);
	}
}

/* Static methods */

void Item::set_opened(Item &target) // static
{
	if (!target.is_opened_)
	{
		target.is_opened_ = true;
		number_of_open_items++;
	}
}

/* Methods for obtaining data. All methods are CONST */

unsigned int Item::get_open_items_num() // const too!
{
	return number_of_open_items;
}

unsigned int Item::get_id() const
{
	return ID;
}

bool Item::is_static() const
{
	return is_static_;
}

bool Item::is_opened() const
{
	return is_opened_;
}

bool Item::has_image() const
{
	return has_image_;
}

bool Item::rect_contains_cursor(sf::Vector2f cursor_position) const
{
	return rect.contains(cursor_position.x, cursor_position.y);
}

sf::String Item::get_name() const
{
	return name;
}

Item_color Item::get_item_colors() const
{
	return item_color;
}

bool Item::check_collision(sf::FloatRect rect) const
{
	return this->rect.intersects(rect);
}

sf::FloatRect Item::get_rect() const
{
	return rect;
}

/* Static variables */

unsigned int Item::number_of_open_items = 0;
