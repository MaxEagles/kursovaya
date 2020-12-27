#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Menu.h"
#include "Functions.h"

int winner_search(Game* g);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1900, 900), "Game", sf::Style::Fullscreen);
	window.setFramerateLimit(60);	

	Game game;
	Menu menu;
	Menu2 menu2;
	Results results;

	sf::Music music;
	music.openFromFile("music.ogg");	
	music.play();
	music.setLoop(true);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (game.active)
					{
						game.game_choice(event.mouseButton.x, event.mouseButton.y);							
					}

					if (menu2.active)
					{
						switch (menu2.menu2_choice(event.mouseButton.x, event.mouseButton.y))
						{
						case 1:
							game.Init(2);
							menu2.active = false;
							game.active = true;
							break;
						case 2:
							game.Init(3);
							menu2.active = false;
							game.active = true;
							break;
						case 3:
							game.Init(4);
							menu2.active = false;
							game.active = true;
							break;
						case 4:
							game.Init(5);
							menu2.active = false;
							game.active = true;
							break;
						default: break;
						}
					}

					if (menu.active)
					{
						switch (menu.menu_choice(event.mouseButton.x, event.mouseButton.y))
						{
						case 1:							
							menu.active = false;
							menu2.active = true;
							break;
						case 2:
							window.close();
							break;
						default: break;
						}
					}		

					if (results.active)
					{
						switch (results.results_choice(event.mouseButton.x, event.mouseButton.y))
						{
						case 1:
							results.active = false;
							menu.active = true;
							break;
						default: break;
						}
					}
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					game.active = false;
					menu2.active = false;
					results.active = false;
					menu.active = true;
				}
			}

			if (game.active)
			{
				for (int i = 0; i < game.n; i++)
				{
					if (game.heroes[i].penalty >= 3)
					{
						game.active = false;
						results.winner = winner_search(&game);
						results.active = true;
					}
				}
				if (game.books == 0)
				{
					game.active = false;
					results.winner = winner_search(&game);
					results.active = true;
				}
			}
		}		

		if (results.active)
		{
			window.clear(my_color);
			window.draw(results);
			window.display();
		}

		if (menu.active)
		{
			window.clear(my_color);
			window.draw(menu);
			window.display();
		}

		if (menu2.active)
		{
			window.clear(my_color);
			window.draw(menu2);
			window.display();
		}

		if (game.active)
		{
			window.clear(my_color);
			window.draw(game);
			window.display();
		}		
	}

	return 0;
}

int winner_search(Game* g)
{
	int max = 0;
	for (int i = 0; i < g->n; i++)
	{
		if (g->heroes[i].penalty < 3)
		{
			if (g->heroes[i].score1 > g->heroes[max].score1)
			{
				max = i;
			}
			else if (g->heroes[i].score1 == g->heroes[max].score1)
			{
				if (g->heroes[i].score2 > g->heroes[max].score2)
				{
					max = i;
				}
				else if (g->heroes[i].score2 == g->heroes[max].score2)
				{
					if (g->heroes[i].penalty < g->heroes[max].penalty)
					{
						max = i;
					}
				}
			}
		}
	}
	return max;
}