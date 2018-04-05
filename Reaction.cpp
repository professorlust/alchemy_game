#include "Reaction.hpp"

Reaction::Reaction(std::vector<unsigned int> input_reagents, std::vector<unsigned int> output_reagents, bool is_sorted)
{
	if (!is_sorted) 
	{
		std::sort(input_reagents.begin(), input_reagents.end());
	}
	this->input_reagents = input_reagents;
	this->output_reagents = output_reagents;
}

Reaction::~Reaction()
{

}

std::vector<unsigned int> Reaction::get_output_reagents()
{
	return output_reagents;
}

std::vector<unsigned int> Reaction::get_input_reagents()
{
	return input_reagents;
}

bool Reaction::check_reaction(std::vector<unsigned int> input_reagents, bool is_sorted)
{
	if (!is_sorted) 
	{
		std::sort(input_reagents.begin(), input_reagents.end());
	}

	if (this->input_reagents == input_reagents)
	{
		return true;
	}
	else
	{
		return false;
	}
}