#include "Reaction.hpp"

Reaction::Reaction(std::vector<unsigned int> input, std::vector<unsigned int> output, bool is_sorted)
{
	if (!is_sorted)
		std::sort(input.begin(), input.end());

	for (auto & i : output)
	{
		output_reagents.push_back(Reagent());
		output_reagents[output_reagents.size()-1].id = i;
	}

	input_reagents = input;
}

Reaction::Reaction(std::vector<unsigned int> input, std::vector<Reagent> output, bool is_sorted)
{
	if (!is_sorted)
		std::sort(input.begin(), input.end());

	output_reagents = output;
	input_reagents = input;
}

Reaction::Reaction(const Reaction &copy)
{
	description = copy.description;
	input_reagents = copy.input_reagents;
	output_reagents = copy.output_reagents;
}

Reaction::~Reaction()
{

}

/* Methods for setting data */

void Reaction::set_description(sf::String description_)
{
	description = description_;
}

/* Methods for obtaining data. All methods are CONST */

std::vector<Reagent> Reaction::get_output_items() const
{
	return output_reagents;
}

std::vector<unsigned int> Reaction::get_input_items() const
{
	return input_reagents;
}

bool Reaction::check_reaction(std::vector<Item*> input, bool is_sorted) const
{
	if (input_reagents.size() == input.size())
	{
		for (int i = 0; i < input.size(); ++i)
		{
			if (input_reagents[i] == input[i]->get_id())
				return true;
		}
	}

	return false;
}

bool Reaction::check_reaction(std::vector<unsigned int> input, bool is_sorted) const
{
	if (!is_sorted)
		std::sort(input.begin(), input.end());

	return (input_reagents == input);
}
