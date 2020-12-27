#pragma once
#include <SFML/Graphics.hpp>
#include "Functions.h"

class Menu : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
public:
	bool active;
	Menu()
	{
		active = true;
		font.loadFromFile("font.otf");
		button1.setSize(sf::Vector2f(500, 150));
		button2.setSize(sf::Vector2f(500, 150));
		button1.setPosition(710, 200);
		button2.setPosition(710, 500);		
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.clear(my_color);

		sf::RectangleShape shape(button1.getSize());
		sf::Text text("New game", font, 55);
		text.setFillColor(sf::Color::Black);
		shape.setFillColor(grey);
		shape.setOutlineThickness(-10);
		shape.setOutlineColor(sf::Color::Black);

		shape.setPosition(button1.getPosition());		
		target.draw(shape, states);
		text.setPosition(830, 240);
		target.draw(text, states);

		shape.setPosition(button2.getPosition());
		target.draw(shape, states);
		text.setPosition(900, 540);
		text.setString("Quit");
		target.draw(text, states);

		text.setPosition(900, 100);
		text.setString("Menu");
		target.draw(text, states);
	}

	int menu_choice(int x, int y)
	{
		if (button_clicked(button1, x, y))
		{
			return 1;
		}
		else if (button_clicked(button2, x, y))
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
};

class Menu2 : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
	sf::RectangleShape button3;
	sf::RectangleShape button4;
public:
	bool active;
	Menu2()
	{
		active = false;
		font.loadFromFile("font.otf");
		button1.setSize(sf::Vector2f(500, 150));
		button2.setSize(sf::Vector2f(500, 150));
		button3.setSize(sf::Vector2f(500, 150));
		button4.setSize(sf::Vector2f(500, 150));
		button1.setPosition(710, 200);
		button2.setPosition(710, 400);
		button3.setPosition(710, 600);
		button4.setPosition(710, 800);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.clear(my_color);

		sf::RectangleShape shape(button1.getSize());
		sf::Text text("2", font, 55);
		text.setFillColor(sf::Color::Black);
		shape.setFillColor(grey);
		shape.setOutlineThickness(-10);
		shape.setOutlineColor(sf::Color::Black);

		shape.setPosition(button1.getPosition());
		target.draw(shape, states);
		text.setPosition(950, 240);
		target.draw(text, states);

		shape.setPosition(button2.getPosition());
		target.draw(shape, states);
		text.setPosition(950, 440);
		text.setString("3");
		target.draw(text, states);

		shape.setPosition(button3.getPosition());
		target.draw(shape, states);
		text.setPosition(950, 640);
		text.setString("4");
		target.draw(text, states);

		shape.setPosition(button4.getPosition());
		target.draw(shape, states);
		text.setPosition(950, 840);
		text.setString("5");
		target.draw(text, states);

		text.setPosition(880, 100);
		text.setString("Players:");
		target.draw(text, states);
	}

	int menu2_choice(int x, int y)
	{
		if (button_clicked(button1, x, y))
		{
			return 1;
		}
		else if (button_clicked(button2, x, y))
		{
			return 2;
		}
		else if (button_clicked(button3, x, y))
		{
			return 3;
		}
		else if (button_clicked(button4, x, y))
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}	
};

class Results : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::RectangleShape button1;
public:
	bool active;
	int winner;
	Results()
	{
		active = false;
		winner = 0;
		font.loadFromFile("font.otf");
		button1.setSize(sf::Vector2f(500, 150));
		button1.setPosition(710, 350);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.clear(my_color);

		sf::RectangleShape shape(button1.getSize());
		sf::Text text("Continue", font, 55);		
		text.setFillColor(sf::Color::Black);
		shape.setFillColor(grey);
		shape.setOutlineThickness(-10);
		shape.setOutlineColor(sf::Color::Black);

		sf::Text victory("", font, 55);
		victory.setFillColor(sf::Color::Black);
		switch (winner)
		{
		case 0: victory.setFillColor(sf::Color::Red);
			victory.setString("Red player victory"); break;
		case 1: victory.setFillColor(sf::Color::Green);
			victory.setString("Green player victory"); break;
		case 2: victory.setFillColor(sf::Color::Blue);
			victory.setString("Blue player victory"); break;
		case 3: victory.setFillColor(sf::Color::Black);
			victory.setString("Yellow player victory"); break;
		case 4: victory.setFillColor(sf::Color::Magenta);
			victory.setString("Purple player victory"); break;
		default: break;
		}

		shape.setPosition(button1.getPosition());
		target.draw(shape, states);
		text.setPosition(850, 400);
		victory.setPosition(700, 250);		
		target.draw(victory, states);
		target.draw(text, states);
	}

	int results_choice(int x, int y)
	{
		if (button_clicked(button1, x, y))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
