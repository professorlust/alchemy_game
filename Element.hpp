#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "defines.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item_color.hpp"

class Element
{
private:
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::FloatRect rect;

	sf::String name;
	sf::String description;

	sf::RectangleShape background;
	sf::Text text_name;

	bool has_image_;
	bool is_move = false;
	bool is_static_ = false;
	bool is_opened_ = false;
	void check_out_the_field(float *x, float *y);

	int adjustment_x = 0;
	int adjustment_y = 0;

	Item_color item_color;

	unsigned int ID = 0; // 0 == error!

	static unsigned int number_of_open_elements;

public:
	/* Constructors */
	Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, const Item_color item_color_ = Item_color(), bool is_static = false);
	Element(sf::String name, sf::String description, unsigned int ID, const Item_color item_color_ = Item_color(), bool is_static = false);
	Element(const Element &element, sf::Vector2f coordinates);
	~Element();

	/* General methods */
	void update(sf::Vector2f coordinates, float time);
	void render(sf::RenderWindow &window);
	void set_position(sf::Vector2f coordinates);
	void set_position_hard(sf::Vector2f coordinates); // set_position() witchout check_out_the_field()
	bool toggle_move(sf::Vector2f coordinates); // Switching motion to ON
	bool toggle_move(); // Switching motion to OFF

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

	/* Static methods */
	static void set_opened(Element &element);
	static unsigned int get_open_elements_num(); // const too!
};
#endif