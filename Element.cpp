#include "Element.hpp"

Element::Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);
	has_image = true;

	rect.height = rect.width = ELEMENT_DIMENSIONS;

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;
}

Element::Element(sf::String name, sf::String description, unsigned int ID, bool is_static)
{
	has_image = false;

	rect.height = rect.width = ELEMENT_DIMENSIONS;

	this->ID = ID;
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
}

Element::Element(const Element &element, sf::Vector2f coordinates)
{
	if (this != &element)
	{
		this->texture = element.texture;
		sprite.setTexture(*texture);
		has_image = element.has_image;

		rect.width = element.rect.width;
		rect.height = element.rect.height;
		set_position(coordinates);

		this->name = element.name;
		this->ID = element.ID;
		is_opened_ = false;
		is_static_ = element.is_static_;
		description = element.description;
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

void Element::update_item_colors()
{

}

void Element::check_out_the_field(float *x, float *y)
{
	if (*y < Y_TOP_BORDER_LINE) *y = Y_TOP_BORDER_LINE;
	if (*y > Y_BOTTOM_BORDER_LINE - ELEMENT_DIMENSIONS) *y = Y_BOTTOM_BORDER_LINE - ELEMENT_DIMENSIONS;
	if (*x < X_LEFT_BORDER_LINE) *x = X_LEFT_BORDER_LINE;
	if (*x > X_RIGHT_BORDER_LINE - ELEMENT_DIMENSIONS) *x = X_RIGHT_BORDER_LINE - ELEMENT_DIMENSIONS;
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

void Element::update(sf::Vector2f cursor_position)
{
	if (is_move)
	{
		float new_x = cursor_position.x - adjustment_x, 
		      new_y = cursor_position.y - adjustment_y;
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

void Element::set_opened(Element &element)
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

unsigned int Element::number_of_open_elements = 0;
sf::Font Element::font = sf::Font();