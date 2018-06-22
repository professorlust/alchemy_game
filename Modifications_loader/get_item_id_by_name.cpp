#include "Modifications_loader.hpp"

unsigned int Modifications_loader::get_item_id_by_name(std::wstring name, const std::vector<Item> &items_list_copy)
{
	for (auto & k : items_list_copy)
		if (k.get_name().toWideString() == name)
			return k.get_id();

	return 0;
}