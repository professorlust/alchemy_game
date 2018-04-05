#ifndef IMAGE_ITEM_HPP
#define IMAGE_ITEM_HPP

#include "Item.hpp"

class Image_item : public Item
{
private:
	sf::Texture* texture;
	sf::Sprite sprite;

public:
	Image_item(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, sf::Vector2f coordinates, uint8_t class_, uint8_t item_type, bool is_static = false);;
	Image_item(const Item* &element, sf::Vector2f coordinates);
	~Image_item();

	// static fun-s from Item
	void update(sf::Vector2f cursor_position, float time);
	void render(sf::RenderWindow &window);
	void set_position(sf::Vector2f coordinates);
	void set_porition_without_COTF(sf::Vector2f coordinates);
};

#endif