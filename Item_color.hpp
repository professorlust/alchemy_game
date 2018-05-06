#ifndef ITEM_COLOR_HPP
#define ITEM_COLOR_HPP

#include <SFML/Graphics.hpp>

struct Item_color
{
	sf::String name;
	sf::Color background;
	sf::Color text;
};

/* Library of standard colors */
// Do not scold the global variables, please ^^
const Item_color AIR_COLOR = { "Air", sf::Color(175, 238, 238, 200), sf::Color(0, 0, 0) };
const Item_color FIRE_COLOR = { "Fire", sf::Color(255, 50, 50, 200), sf::Color(0, 0, 0) };
const Item_color EARTH_COLOR = { "Earth", sf::Color(139, 69, 19, 200), sf::Color(224, 219, 168) };
const Item_color WATER_COLOR = { "Water", sf::Color(70, 130, 180, 200), sf::Color(0, 0, 0) };
const Item_color LIGHT_GREEN_COLOR = { "Light green", sf::Color(173, 255, 47, 200), sf::Color(0, 0, 0) };
const Item_color PURPLE_COLOR = { "Purple", sf::Color(199, 21, 133, 200), sf::Color(0, 0, 0) };
const Item_color GREY_COLOR = { "Grey", sf::Color(199, 199, 199, 200), sf::Color(0, 0, 0) };
const Item_color LIGHT_PINK_COLOR = { "Light pink", sf::Color(255, 160, 122, 200), sf::Color(0, 0, 0) };
const Item_color DARK_COLOR = { "Dark", sf::Color(0, 0, 0, 200), sf::Color(255, 255, 255) };
const Item_color DARK_RED_COLOR = { "Dark red", sf::Color(139, 0, 0, 200), sf::Color(0, 0, 0) };
const Item_color DARK_BLUE_COLOR = { "Dark blue", sf::Color(0, 0, 139, 200), sf::Color(150, 150, 150) };
const Item_color ORANGE_COLOR = { "Orange", sf::Color(255, 165, 0, 200), sf::Color(0, 0, 0) };
const Item_color DARK_GREEN_COLOR = { "Dark green", sf::Color(0, 100, 0, 200), sf::Color(0, 0, 0) };

#endif