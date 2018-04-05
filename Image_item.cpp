#include "Image_item.hpp"

Image_item::Image_item(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, sf::Vector2f coordinates, uint8_t class_, uint8_t item_type, bool is_static)
{
	this->texture = texture;
	sprite.setTexture(*texture);

	rect.height = rect.width = ELEMENT_DIMENSIONS;
	set_position(coordinates);

	this->ID = ID;
	this->name = name;

	this->is_static_ = is_static;
	is_opened_ = false;
	this->description = description;

	this->item_type = item_type;
	this->class_ = class_;
}

Image_item::Image_item(const Item* &element, sf::Vector2f coordinates)
{
	if (this != &element)
	{
		this->texture = element.texture;
		sprite.setTexture(*texture);

		rect.height = rect.width = ELEMENT_DIMENSIONS;
		set_position(coordinates);

		name = element.name;
		ID = element.ID;
		item_type = element.item_type;
		class_ = element.class_;
		is_opened_ = false;
		is_static_ = element.is_static_;
		description = element.description;
	}
}

Image_item::~Image_item()
{

}

void Image_item::update(sf::Vector2f cursor_position, float time)
{
	if (is_move_)
	{
		set_position(cursor_position);
	}
}

void Image_item::render(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Image_item::set_position(sf::Vector2f coordinates)
{
	float new_x = coordinates.x - adjustment_x;
	float new_y = coordinates.y - adjustment_y;

	check_out_the_field(&new_x, &new_y);
	rect.left = new_x;
	rect.top = new_y;
	sprite.setPosition(rect.left, rect.top);
}

void Image_item::set_porition_without_COTF(sf::Vector2f coordinates)
{
	rect.left = coordinates.x;
	rect.top = coordinates.y;
	sprite.setPosition(rect.left, rect.top);
}