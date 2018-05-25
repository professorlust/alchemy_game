#include "load_game_data_from_file.hpp"

bool load_game_data_from_file(std::vector<Item*> &items_list_copy, std::vector<Reaction*> &reactions_list_copy, std::vector<unsigned int> &started_items_copy, std::string file_name)
{
	items_list_copy.clear();
	reactions_list_copy.clear();
	started_items_copy.clear();

	std::vector<Item_color> item_colors;
	std::ifstream file(file_name);
	if (!file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string buffer;

	bool top_panel_render = false;

	/* Settigs block */
	while (getline(file, buffer)
		  && buffer != "colors:")
	{
		if (buffer.size() == 0 || // Skipping empty lines
			buffer[0] == '#')
			continue;

		std::string argument, operator_, value;

		for (int i = 0, step = 0; i < buffer.size(); ++i)
		{	
			if (buffer[i] == '#') // Beginning of comments block 
				break;

			if (step == 0)
			{
				if (buffer[i] != ' ')
					argument += buffer[i];
				else
					step++;
			}
			else if (step == 1)
			{
				if (buffer[i] != ' ')
					operator_ += buffer[i];
				else
					step++;
			}
			else // if step == 2
			{
				value += buffer[i];
			}
		}

		if (argument == "top_element_panel")
			top_panel_render = (value == "true" || value == "1") ? true : false;
	}

	/* Colors block */
	while (getline(file, buffer)
		  && buffer != "elements:")
	{
		if (buffer.size() == 0 || // Skipping empty lines
			buffer[0] == '#')
			continue;

		std::string name;
		sf::Color text_color(0, 0, 0);
		sf::Color background_color(255, 255, 255);

		int iterator = 0;

		/* Removing blank spaces */
		bool in_quotes = false;
		while (iterator < buffer.size())
		{
			if (buffer[iterator] == '"')
				in_quotes = !in_quotes;

			if (buffer[iterator] == ' ' &&
				!in_quotes)
				buffer.erase(buffer.begin()+iterator);
			else
				iterator++;
		}
		iterator = 1; // skip the symbol "

		/* Getting name */
		while (buffer[iterator] != '"')
		{
			name += buffer[iterator];
			iterator++;
		}
		iterator++; // skip the symbol "

		/* Getting colors */
		// argument (background / text)
		for (int i = 0; i < 2; ++i)
		{
			std::string argument;
			while (buffer[iterator] != '(' &&
				   buffer[iterator] != ')')
			{
				argument += buffer[iterator];
				iterator++;
			}
			iterator++; // skip the symbol (

			std::string r_string;
			while (buffer[iterator] != ',' &&
				   buffer[iterator] != ')')
			{
				r_string += buffer[iterator];
				iterator++;
			}
			iterator++; // skip the symbol ,

			std::string g_string;
			while (buffer[iterator] != ',' &&
				   buffer[iterator] != ')')
			{
				g_string += buffer[iterator];
				iterator++;
			}
			iterator++; // skip the symbol ,

			std::string b_string;
			while (buffer[iterator] != ',' &&
				   buffer[iterator] != ')')
			{
				b_string += buffer[iterator];
				iterator++;
			}
			iterator++; // skip the symbol ,
			
			if (argument == "background")
				background_color = sf::Color(atoi(r_string.c_str()), atoi(g_string.c_str()), atoi(b_string.c_str()));
			else if (argument == "text")
				text_color = sf::Color(atoi(r_string.c_str()), atoi(g_string.c_str()), atoi(b_string.c_str()));
		}
	}
}

/*
Структура файла с модом (нельзя нарушать):
1. Настройки

2. Цвета элементов без картинки. Порядок фон/текст неважен
2.1 формат цвета: "имя" background(R G B) text(R G B)

3. Список элементов. Подробное описание и порядок:
3.1 Обязательные параметры идут в таком порядке:
тип (element / counter / timer). На данный момент реализован только element. Подробнее про другие типы будет написано после появления данных типов в игре
имя элемента в двойных или одинарных ковычках.
Дополнительные параметры (***порядок не важен***): static, image(путь), color(тип цвета из 2 пункта или стандартных по имени), 

4. Список реакций формата: имя1 + имя2 + имя3 ... + имяN = имя1 + имя4 + имя6 ... + имяN
Для комментариев используется символ решетки: #
======================
ПРИМЕР ВХОДНОГО ФАЙЛА:
settings:
top_element_panel = false

colors:
"My color" background(50, 150, 0) text(52, 70, 30)

elements:
element "Вода" image(water.png) # Элемент воды с картинкой
element "Огонь" static color(FIRE_COLOR) # Элемент огня, статичный (нельзя удалить и создать новую копию), цвет фона и текста fire
element "Земля" static image(water.png) color(FIRE_COLOR)

reactions:
Вода + Огонь = Земля

*/

// ЕЩЕ СОЗДАТЬ ФУНКЦИЮ ДЛЯ ПРОВЕРКИ СИНТАКСИСА