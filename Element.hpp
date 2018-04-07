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
	void output_field_adjustment(float *x, float *y);

	static sf::RectangleShape *item_name_rect;
	static sf::Text *item_name_text;
	static bool is_initiated;

	int deflection_y = 0;
	int deflection_x = 0; // отклонения при клике. от подергиваний

	unsigned int ID = 0; // 0 == error!

	static unsigned int number_of_open_elements;

public:
	void update(sf::Vector2f cursor_position);
	bool enable_move(int d_x, int d_y); // Returns true if the item has not moved and toggle move to true
	bool disabling_move(); // Returns true if the item has moved and toggle move to false
	void render(sf::RenderWindow &window);
	void render_name(sf::RenderWindow &window, float x, float y);
	bool check_collision(sf::FloatRect rect);
	sf::FloatRect get_rect();
	unsigned int get_id(); // Returns ID of element (unsigned int)
	void set_position(float new_x, float new_y);
	void qwerty(float new_x, float new_y);
	bool is_static();
	bool is_opened();
	bool rect_contains_cursor(float x, float y);
	sf::String get_name();

	static void set_opened(Element &element);
	static unsigned int get_open_elements_num();
	static void initialization(sf::Font *font);
	
	Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, float spawn_position_x = 0, float spawn_position_y = 0, bool is_static = false);
	Element(sf::String name, sf::String description, unsigned int ID, float spawn_position_x = 0, float spawn_position_y = 0, bool is_static = false);
	Element(const Element &element, float spawn_position_x = 0, float spawn_position_y = 0);
	~Element();	
};
#endif