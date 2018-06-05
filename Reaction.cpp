#include "Reaction.hpp"

Reaction::Reaction(std::vector<unsigned int> input_reagents, std::vector<unsigned int> output_reagents, bool is_sorted)
{
	if (!is_sorted)
		std::sort(input_reagents.begin(), input_reagents.end());

	this->input_reagents = input_reagents;
	this->output_reagents = output_reagents;
}

Reaction::Reaction(const Reaction &reaction)
{
	description = reaction.description;
	input_reagents = reaction.input_reagents;
	output_reagents = reaction.output_reagents;
}

Reaction::~Reaction()
{

}

/* Methods for setting data */

void Reaction::set_description(sf::String description)
{
	this->description = description;
}

/* Methods for obtaining data. All methods are CONST */

std::vector<unsigned int> Reaction::get_output_items() const
{
	return output_reagents;
}

std::vector<unsigned int> Reaction::get_input_items() const
{
	return input_reagents;
}

bool Reaction::check_reaction(std::vector<Item*> input_reagents, bool is_sorted) const
{
	if (this->input_reagents.size() == input_reagents.size())
	{
		for (unsigned int i = 0; i < input_reagents.size(); ++i)
		{
			if (this->input_reagents[i] == input_reagents[i]->get_id())
				return true;
		}
	}

	return false;
}

bool Reaction::check_reaction(std::vector<unsigned int> input_reagents, bool is_sorted) const
{
	if (!is_sorted)
		std::sort(input_reagents.begin(), input_reagents.end());

	return (input_reagents == this->input_reagents);
}
