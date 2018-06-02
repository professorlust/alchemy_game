#include "Modifications_loader.hpp"

void Modifications_loader::initialization_started_items()
{
	if (process.size() == 0)
		return;

	std::string item_name = process;

	for (int i = 0; i < items_list.size(); ++i)
		if (item_name == items_list[i].get_name())
		{
			started_items.push_back(items_list[i].get_id());
			return;
		}

	// if name not found
	std::cout << process << ": started item not found." << std::endl;
}