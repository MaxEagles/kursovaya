#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Functions.h"

class Cell
{
public:
	sf::RectangleShape shape;
	int value;
	Hero* hero;
	bool is_tp;
	Cell()
	{
		shape.setSize(sf::Vector2f(150, 150));
		shape.setOutlineThickness(-5);
		shape.setOutlineColor(sf::Color::Black);
		shape.setFillColor(grey);
		value = 0;
		hero = NULL;
		is_tp = false;
	}
};
