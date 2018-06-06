#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.hpp"
#include "Item_color.hpp"

class Item
{
private:
	/* General Variables */
	sf::String name;
	sf::String description;
	unsigned int ID = 0; // 0 == error!

	bool has_image_;
	bool is_move = false;
	bool is_static_ = false;
	bool is_opened_ = false;
	void check_out_the_field(float *x, float *y) const;

	int adjustment_x = 0;
	int adjustment_y = 0;

	/* Variables for items with a picture */
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::FloatRect rect;

	/* Variables for items without a texture */
	sf::RectangleShape background;
	sf::Text text_name;
	Item_color item_color;

	static unsigned int number_of_open_items;

public:
	Item(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, const Item_color item_color_ = Item_color(), bool is_static = false);
	Item(sf::String name, sf::String description, unsigned int ID, const Item_color item_color_ = Item_color(), bool is_static = false);
	Item(const Item &copy, sf::Vector2f coordinates);
	~Item();

	/* General methods */
	void update(sf::Vector2f coordinates, float time);
	void render(sf::RenderWindow &window);
	bool toggle_move(sf::Vector2f coordinates); // Switching motion to ON
	bool toggle_move(); // Switching motion to OFF

	/* Methods for setting data */
	void set_position(sf::Vector2f coordinates);
	void set_position_hard(sf::Vector2f coordinates); // set_position() witchout check_out_the_field()
	void set_opened();

	/* Methods for obtaining data. All methods are CONST */
	bool is_static() const;
	bool is_opened() const;
	bool rect_contains_cursor(sf::Vector2f cursor_position) const;
	bool check_collision(sf::FloatRect rect) const;
	bool has_image() const;
	unsigned int get_id() const;
	sf::FloatRect get_rect() const;
	sf::String get_name() const;
	Item_color get_item_colors() const;
};
#endif