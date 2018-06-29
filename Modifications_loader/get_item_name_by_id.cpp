#include "Modifications_loader.hpp"

sf::String Modifications_loader::get_item_name_by_id(unsigned int id, const std::vector<Item> &items_list_copy)
{
	for (auto & k : items_list_copy)
		if (k.get_id() == id)
			return k.get_name();

	return sf::String("NULL");
}