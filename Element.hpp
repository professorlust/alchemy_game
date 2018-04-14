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

	void update_item_colors();

	int type = 0;
	unsigned int ID = 0; // 0 == error!

	static unsigned int number_of_open_elements;
	static sf::Font font;

public:
	/* Constructors */
	Element(sf::Texture* texture, sf::String name, sf::String description, unsigned int ID, int type = 0, bool is_static = false);
	Element(sf::String name, sf::String description, unsigned int ID, int type = 0, bool is_static = false);
	Element(const Element &element, sf::Vector2f coordinates);
	~Element();

	/* General methods */
	void update(sf::Vector2f coordinates, float time);
	void render(sf::RenderWindow &window);
	void set_position(sf::Vector2f coordinates);
	void set_position_hard(sf::Vector2f coordinates); // witchout check_out_the_field()
	bool toggle_move(sf::Vector2f coordinates); // ON
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

/* Element будет переименован в Item позже. 
Названия ID классов элемента, в зависимости от которых выбирается
цвет рамки и текста при наведении на элемент / его отображении без картинки */
enum item_classes
{
	NONE = 0, // Back(255, 255, 255); Text(0, 0, 0)
	AIR, //
	WATER, //
	FIRE, //
	EARTH, //
	PLANT, //
	ANIMAL, //
	MAGIC, //
	CIVILIZATION, // or technology?
	HUMAN, //
	FOOD, //
	DARK, //
	OTHER, //
	DARK_BLUE, //
	CRIMSON, // 
	ORANGE, //
	JUNGLE, //
	EVIL //
};

#endif