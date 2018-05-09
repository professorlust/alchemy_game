#include "Config.hpp"

Config::Config(std::string file_p)
{
	// WINDOW_H and WINDOW_W in defines.cpp
	GLOBAL_FONT.loadFromFile("lucon.ttf");

	file.open(file_p);
	if (file.is_open())
	{
		load_from_file();
	}
	file.close();
}

Config::~Config()
{

}

void Config::load_from_file()
{
	/*
		Каждая строка имеет такой формат: "переменная оператор переменная" (примеры: font = arial.ttf ; width = 500)
		На данный момент оператор нигде не учитывается.
		Я попытаюсь сделать парсинг конфига самостоятельно, если получится. Кривой очень, конечно.
		В argument - что принмается. в operator - действие (пока что только = будет). В value - значение.
		Значение приводится к тому типу, которое нужно аргументу.
		Те аргументы, которые не были назначены забиваются стандартными значениями.
	*/
	std::string buffer;

	/* Флаги загрузки аргументов */
	bool font_loaded = false, // шрифт
	width_loaded = false, // высота
	height_loaded = false; // и так далее, понятно из названия

	while (std::getline(file, buffer))
	{
		std::string argument, operator_, value;

		/*Кривой парсинг строки*/
		for (int i = 0, step = 0; i < buffer.size(); ++i)
		{
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
			else if (step == 2) 
			{
				value += buffer[i];
			}
		}

		/* Перебор вариантов аргументов */
		if (argument == "font" & !font_loaded)
		{
			GLOBAL_FONT.loadFromFile(value);
			font_loaded = true;
		}
		else if (argument == "width" & !width_loaded)
		{
			int window_w = atoi(value.c_str());

			if (window_w > 64)
				WINDOW_W = window_w;
			else
				WINDOW_W = 64;

			width_loaded = true;
		}
		else if (argument == "height" & !height_loaded)
		{
			int window_h = atoi(value.c_str());

			if (window_h > 96)
				WINDOW_H = window_h;
			else
				WINDOW_H = 96;

			height_loaded = true;
		}
	}
}