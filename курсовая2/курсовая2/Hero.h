#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Cell.h"
#include "Functions.h"

class Hero
{
public:
	sf::CircleShape shape;
	int position1;
	int position2;
	int penalty;
	int score1;
	int score2;
	Card cards[3];	
	Hero()
	{
		shape.setRadius(50);
		shape.setOutlineColor(sf::Color::Transparent);
		shape.setOutlineThickness(-2);
		shape.setFillColor(sf::Color::White);
		penalty = 0;
		score1 = 0;
		score2 = 0;
		position1 = position2 = 0;		
	}
};
