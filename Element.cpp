#include "Element.hpp"

Element::Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, const Item_color item_color_, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);
	has_image_ = true;

	rect.left = rect.left = 0;
	rect.height = rect.width = ITEM_DIMENSIONS;

	item_color = item_color_;

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;
}

Element::Element(sf::String name, sf::String description, unsigned int ID, const Item_color item_color_, bool is_static)
{
	has_image_ = false;

	rect.left = rect.left = 0;
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
	text_name.setFont(GLOBAL_FONT);
	text_name.setString(name);
}

Element::Element(const Element &element, sf::Vector2f coordinates)
{
	if (this != &element)
	{
		has_image_ = element.has_image_;
		if (has_image_)
		{
			texture = element.texture;
			sprite.setTexture(*texture);
		}

		name = element.name;
		ID = element.ID;
		is_opened_ = false;
		is_static_ = element.is_static_;
		description = element.description;

		rect.width = element.rect.width;
		rect.height = element.rect.height;
		set_position(coordinates);

		item_color = element.item_color;

		background.setFillColor(item_color.background);
		background.setSize(sf::Vector2f(name.getSize()*10, 16));

		text_name.setCharacterSize(16);
		text_name.setFillColor(item_color.text);
		text_name.setFont(GLOBAL_FONT);
		text_name.setString(name);
	}
}

Element::~Element()
{
	
}

void Element::render(sf::RenderWindow &window)
{
	if (has_image_)
	{
		window.draw(sprite);
	}
	else
	{
		window.draw(background);
		window.draw(text_name);
	}
}

void Element::check_out_the_field(float *x, float *y)
{
	int y_top_border = BORDERS.top,
	y_bottom_border = BORDERS.top + BORDERS.height,
	x_left_border = BORDERS.left,
	x_right_border = BORDERS.left + BORDERS.width;

	if (*y < y_top_border) *y = y_top_border;
	if (*y > y_bottom_border - ITEM_DIMENSIONS) *y = y_bottom_border - rect.height;
	if (*x < x_left_border) *x = x_left_border;
	if (*x > x_right_border - ITEM_DIMENSIONS) *x = x_right_border - rect.width;
}

void Element::set_position(sf::Vector2f coordinates)
{
	check_out_the_field(&coordinates.x, &coordinates.y);
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image_)
	{
		sprite.setPosition(coordinates.x, coordinates.y);
	}
	else
	{
		background.setPosition(coordinates.x, coordinates.y);
		text_name.setPosition(coordinates.x, coordinates.y);
	}
}

void Element::update(sf::Vector2f coordinates, float time)
{
	if (is_move)
	{
		float new_x = coordinates.x - adjustment_x, 
		      new_y = coordinates.y - adjustment_y;
		check_out_the_field(&new_x, &new_y);
		rect.left = new_x;
		rect.top = new_y;
		if (has_image_)
		{
			sprite.setPosition(rect.left, rect.top);
		}
		else
		{
			background.setPosition(rect.left, rect.top);
			text_name.setPosition(rect.left, rect.top);
		}
	}
}

bool Element::toggle_move()
{
	if (is_move)
	{
 		is_move = false;
 		return true;
 	}
 	else return false;
}

bool Element::toggle_move(sf::Vector2f cursor_position)
{
	if (!is_move)
	{
		adjustment_x = cursor_position.x - rect.left;
		adjustment_y = cursor_position.y - rect.top;
		is_move = true;
		return true;
	}
	else return false;
}


void Element::set_opened(Element &element) // static
{
	if (!element.is_opened_)
	{
		element.is_opened_ = true;
		number_of_open_elements++;
	}
}

void Element::set_position_hard(sf::Vector2f coordinates)
{
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image_)
	{
		sprite.setPosition(coordinates.x, coordinates.y);
	}
	else
	{
		background.setPosition(coordinates.x, coordinates.y);
		text_name.setPosition(coordinates.x, coordinates.y);
	}
}

unsigned int Element::get_open_elements_num() // const too!
{
	return number_of_open_elements;
}

unsigned int Element::get_id() const
{
	return ID;
}

bool Element::is_static() const
{
	return is_static_;
}

bool Element::is_opened() const
{
	return is_opened_;
}

bool Element::has_image() const
{
	return has_image_;
}

bool Element::rect_contains_cursor(sf::Vector2f cursor_position) const
{
	return rect.contains(cursor_position.x, cursor_position.y);
}

sf::String Element::get_name() const
{
	return name;
}

Item_color Element::get_item_colors() const
{
	return item_color;
}

bool Element::check_collision(sf::FloatRect rect) const
{
	return this->rect.intersects(rect);
}

sf::FloatRect Element::get_rect() const
{
	return rect;
}

unsigned int Element::number_of_open_elements = 0;