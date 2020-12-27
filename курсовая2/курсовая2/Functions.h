#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

sf::Color my_color(240, 230, 175);
sf::Color grey(195, 195, 195);

bool button_clicked(sf::RectangleShape button, int x, int y)
{
	if (x > button.getPosition().x&& x<button.getSize().x + button.getPosition().x && y>button.getPosition().y&& y < button.getSize().y + button.getPosition().y)
	{
		return true;
	}
	return false;
}
