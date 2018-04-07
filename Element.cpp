#include "Element.hpp"

unsigned int Element::number_of_open_elements = 0;
sf::RectangleShape* Element::item_name_rect = new sf::RectangleShape;
sf::Text* Element::item_name_text = new sf::Text;
bool Element::is_initiated = false;

Element::Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, float spawn_position_x, float spawn_position_y, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);
	has_image = true;

	rect.height = rect.width = ELEMENT_DIMENSIONS;
	set_position(spawn_position_x, spawn_position_y);

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;
}

Element::Element(sf::String name, sf::String description, unsigned int ID, float spawn_position_x, float spawn_position_y, bool is_static)
{
	has_image = false;

	rect.height = rect.width = ELEMENT_DIMENSIONS;
	set_position(spawn_position_x, spawn_position_y);

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;
}

Element::Element(const Element &element, float spawn_position_x, float spawn_position_y)
{
	if (this != &element)
	{
		this->texture = element.texture;
		sprite.setTexture(*texture);
		has_image = element.has_image;

		rect.width = element.rect.width;
		rect.height = element.rect.height;
		set_position(spawn_position_x, spawn_position_y);

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

	}
}

void Element::output_field_adjustment(float *x, float *y)
{
	if (*y < Y_TOP_BORDER_LINE) *y = Y_TOP_BORDER_LINE;
	if (*y > Y_BOTTOM_BORDER_LINE - ELEMENT_DIMENSIONS) *y = Y_BOTTOM_BORDER_LINE - ELEMENT_DIMENSIONS;
	if (*x < X_LEFT_BORDER_LINE) *x = X_LEFT_BORDER_LINE;
	if (*x > X_RIGHT_BORDER_LINE - ELEMENT_DIMENSIONS) *x = X_RIGHT_BORDER_LINE - ELEMENT_DIMENSIONS;
}

void Element::set_position(float new_x, float new_y)
{
	output_field_adjustment(&new_x, &new_y);
	rect.left = new_x;
	rect.top = new_y;
	sprite.setPosition(rect.left, rect.top);
}

void Element::update(sf::Vector2f cursor_position)
{
	if (is_move)
	{
		float new_x = cursor_position.x - deflection_x, 
		      new_y = cursor_position.y - deflection_y;
		output_field_adjustment(&new_x, &new_y);
		rect.left = new_x;
		rect.top = new_y;
		sprite.setPosition(rect.left, rect.top);
	}
}

bool Element::check_collision(sf::FloatRect rect)
{
	return (this->rect.intersects(rect));
}

sf::FloatRect Element::get_rect()
{
	return rect;
}

/* Returns true if the item has not moved */
bool Element::enable_move(int d_x, int d_y)
{
	if (!is_move)
	{
		deflection_x = d_x;
		deflection_y = d_y;
 		is_move = true;
 		return true;
 	}
 	else return false;
}

 /* Returns true if the item has moved */
bool Element::disabling_move()
{
	if (is_move)
	{
 		is_move = false;
 		return true;
 	}
 	else return false;
}

unsigned int Element::get_id()
{
	return ID;
}

bool Element::is_static()
{
	return is_static_;
}

bool Element::is_opened()
{
	return is_opened_;
}

void Element::set_opened(Element &element)
{
	element.is_opened_ = true;
	number_of_open_elements++;
}

void Element::qwerty(float new_x, float new_y)
{
	rect.left = new_x;
	rect.top = new_y;
	sprite.setPosition(new_x, new_y);
}

unsigned int Element::get_open_elements_num()
{
	return number_of_open_elements;
}

void Element::render_name(sf::RenderWindow &window, float x, float y)
{
	item_name_rect->setPosition(x- (name.getSize()+1) *7 - 5, y);
	item_name_text->setPosition(x- (name.getSize()+1) *7 - 5, y);
	item_name_text->setString(name);
	item_name_rect->setSize(sf::Vector2f(name.getSize()*7 + 5, 16));

	window.draw(*item_name_rect);
	window.draw(*item_name_text);
}

void Element::initialization(sf::Font *font)
{
	if (!is_initiated)
	{
		item_name_text->setCharacterSize(16);
		item_name_text->setFillColor(sf::Color(0, 0, 0));
		item_name_text->setFont(*font);
		item_name_rect->setFillColor(sf::Color(255, 243, 154));
	}
	is_initiated = true;
}

bool Element::rect_contains_cursor(float x, float y)
{
	return (rect.contains(x, y));
}

sf::String Element::get_name()
{
	return name;
}