#include "Modifications_loader.hpp"

void Modifications_loader::remove_spaces(std::wstring &string, bool remove_quotes)
{
	bool in_quotes = false;
	unsigned int i = 0;

	for (unsigned int i = 0; i < string.size();)
	{
		if (string[i] == L'"' ||
			string[i] == L'\'')
		{
			if (remove_quotes)
				string.erase(string.begin() + i);
			else
				i++;

			in_quotes = !in_quotes;
		}

		else if (!in_quotes &&
			string[i] == L' ')
			string.erase(string.begin() + i);

		else i++;
	}
}