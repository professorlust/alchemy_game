#include "Reagent.hpp"

bool Reagent::check_conditions(const std::vector<Item> items_list, const std::vector<Item> items_on_map, unsigned int last_item)
{
	int a = rand() % 10001;
	if ( chance <= a )
		return false;

	unsigned int found_on_map_condition_counter = 0;
	bool found_on_map_condition = false;

	if (!found_on_map.empty())
	{
		std::vector<unsigned int> counted;

		auto is_counted = [&counted](unsigned int _iterator) -> bool const
		{
			for (auto & i : counted)
				if (i == _iterator)
					return true; // for []()is_counted

			return false; // for []()is_counted
		};

		for (auto & found : found_on_map)
		{
			for (unsigned int i = 0; i < last_item; ++i)
			{
				if (found == items_on_map[i].get_id() && !is_counted(i))
				{
					found_on_map_condition_counter++;
					counted.push_back(i);
					break;
				}
			}
		}

		found_on_map_condition = (found_on_map_condition_counter == found_on_map.size());
	}
	else
		found_on_map_condition = true;

	bool not_found_on_map_condition = false;
	if (!not_found_on_map.empty())
	{
		bool founded = false;

		for (auto & found : not_found_on_map)
		{
			for (unsigned int i = 0; i < last_item; ++i)
			{
				if (items_on_map[i].get_id() == found)
				{
					founded = true;
					break;
				}
			}

			if (founded)
				break;
		}

		not_found_on_map_condition = !founded;
	}
	else
		not_found_on_map_condition = true;

	bool items_is_not_open_condition = false;
	if (!items_is_not_open.empty())
	{
		unsigned int items_is_not_open_condition_counter = 0;

		for (auto & i : items_is_not_open)
		{
			for (auto & j : items_list)
			{
				if (i == j.get_id() &&
					!j.is_opened())
				{
					items_is_not_open_condition_counter++;
					break;
				}
			}
		}
		items_is_not_open_condition = (items_is_not_open_condition_counter == items_is_not_open.size());
	}
	else
		items_is_not_open_condition = true;

	bool items_is_open_condition = false;
	if (!items_is_open.empty())
	{
		unsigned int items_is_open_condition_counter = 0;

		for (auto & i : items_is_open)
		{
			for (auto & j : items_list)
			{
				if (i == j.get_id() &&
					j.is_opened())
				{
					items_is_open_condition_counter++;
					break;
				}
			}
		}
		items_is_open_condition = (items_is_open_condition_counter == items_is_open.size());
	}
	else
		items_is_open_condition = true;

	return found_on_map_condition && not_found_on_map_condition && items_is_open_condition && items_is_not_open_condition;
}