#include "defines.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ELEMENT_HPP
#define ELEMENT_HPP
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

	bool has_image;
	bool is_move = false;
	bool is_static_ = false;
	bool is_opened_ = false;
	void check_out_the_field(float *x, float *y);

	int adjustment_x = 0;
	int adjustment_y = 0;

	unsigned int ID = 0; // 0 == error!

	static unsigned int number_of_open_elements;
	static sf::Font font;

public:
	/* Constructors */
	Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, float spawn_position_x = 0, float spawn_position_y = 0, bool is_static = false);
	Element(sf::String name, sf::String description, unsigned int ID, float spawn_position_x = 0, float spawn_position_y = 0, bool is_static = false);
	Element(const Element &element, float spawn_position_x = 0, float spawn_position_y = 0);
	~Element();	

	/* General methods */
	void update(sf::Vector2f cursor_position);
	void render(sf::RenderWindow &window);
	void set_position(float new_x, float new_y);
	void set_position_hard(float new_x, float new_y); // witchout check_out_the_field()
	bool toggle_move(sf::Vector2f cursor_position); // ON
	bool toggle_move(); // OFF

	/* Methods for obtaining data. CONST */
	bool is_static() const;
	bool is_opened() const;
	bool rect_contains_cursor(float x, float y) const;
	bool check_collision(sf::FloatRect rect) const;
	unsigned int get_id() const;
	sf::FloatRect get_rect() const;
	sf::String get_name() const;

	/* Static methods */
	static void set_opened(Element &element);
	static unsigned int get_open_elements_num(); // const too!
	static void load_new_font(sf::Font font_);
};
#endif