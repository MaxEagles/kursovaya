#pragma once
#include <SFML/Graphics.hpp>

class Card
{
public:
	int value1;
	int value2;
	int value3;
	void new_card()
	{
		srand(time(NULL));
		value1 = rand() % 4 + 1;
		value2 = rand() % 4 + 1;
		value3 = rand() % 4 + 1;
	}
};
