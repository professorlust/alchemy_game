#include "Element.hpp"

Element::Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, int type, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);
	has_image = true;

	rect.left = rect.left = 0;
	rect.height = rect.width = ELEMENT_DIMENSIONS;

	this->ID = ID;
	this->type = type;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;

	update_item_colors();
}

Element::Element(sf::String name, sf::String description, unsigned int ID, int type, bool is_static)
{
	has_image = false;

	rect.left = rect.left = 0;
	rect.width = name.getSize()*10;
	rect.height = 16;

	this->ID = ID;
	this->type = type;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;

	background.setFillColor(sf::Color(200, 200, 200)); // Light grey
	background.setSize(sf::Vector2f(name.getSize()*10, 16));

	text_name.setCharacterSize(16);
	text_name.setFillColor(sf::Color(0, 0, 0));
	text_name.setFont(font);
	text_name.setString(name);

	update_item_colors();
}

Element::Element(const Element &element, sf::Vector2f coordinates)
{
	if (this != &element)
	{
		has_image = element.has_image;
		if (has_image)
		{
			texture = element.texture;
			sprite.setTexture(*texture);
		}

		name = element.name;
		ID = element.ID;
		type = element.type;
		is_opened_ = false;
		is_static_ = element.is_static_;
		description = element.description;

		rect.width = element.rect.width;
		rect.height = element.rect.height;
		set_position(coordinates);

		background.setFillColor(sf::Color(200, 200, 200)); // Light grey
		background.setSize(sf::Vector2f(name.getSize()*10, 16));

		text_name.setCharacterSize(16);
		text_name.setFillColor(sf::Color(0, 0, 0));
		text_name.setFont(font);
		text_name.setString(name);

		update_item_colors();
	}
}

Element::~Element()
{
	
}

void Element::render(sf::RenderWindow &window)
{
	if (has_image)
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
	if (*y < Y_TOP_BORDER_LINE) *y = Y_TOP_BORDER_LINE;
	if (*y > Y_BOTTOM_BORDER_LINE - rect.height) *y = Y_BOTTOM_BORDER_LINE - rect.height;
	if (*x < X_LEFT_BORDER_LINE) *x = X_LEFT_BORDER_LINE;
	if (*x > X_RIGHT_BORDER_LINE - rect.width) *x = X_RIGHT_BORDER_LINE - rect.width;
}

void Element::set_position(sf::Vector2f coordinates)
{
	check_out_the_field(&coordinates.x, &coordinates.y);
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image)
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
		if (has_image)
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

bool Element::check_collision(sf::FloatRect rect) const
{
	return (this->rect.intersects(rect));
}

sf::FloatRect Element::get_rect() const
{
	return rect;
}

bool Element::toggle_move() // TURN OFF
{
	if (is_move)
	{
 		is_move = false;
 		return true;
 	}
 	else return false;
}

bool Element::toggle_move(sf::Vector2f cursor_position) // TURN ON
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

void Element::set_opened(Element &element) // static
{
	element.is_opened_ = true;
	number_of_open_elements++;
}

void Element::set_position_hard(sf::Vector2f coordinates)
{
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	if (has_image)
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

bool Element::rect_contains_cursor(float x, float y) const
{
	return (rect.contains(x, y));
}

sf::String Element::get_name() const
{
	return name;
}

void Element::load_new_font(sf::Font font_)
{
	font = font_;
}

void Element::update_item_colors()
{
	switch (type)
	{
		case NONE: // == OTHER
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case OTHER: // == NONE
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case AIR:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case WATER:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case FIRE:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));	
		}

		case EARTH:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case PLANT:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case ANIMAL:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case MAGIC:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case CIVILIZATION:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case HUMAN:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case FOOD:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case CRIMSON:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case DARK_BLUE:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}

		case ORANGE:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));	
		}

		case JUNGLE:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));		
		}

		case EVIL:
		{
			background.setFillColor(sf::Color(0, 0, 0));
			text_name.setFillColor(sf::Color(0, 0, 0));
		}
	}
}

unsigned int Element::number_of_open_elements = 0;
sf::Font Element::font = sf::Font();