#pragma once
#include "Cell.h"
#include "Card.h"
#include "Hero.h"
#include "Functions.h"

class Game : public sf::Drawable, public sf::Transformable
{
private:		
	sf::Texture v1_texture;
	sf::Texture v2_texture;
	sf::Texture v3_texture;
	sf::Texture v4_texture;
	sf::Texture tp_texture;
	sf::Texture boss_texture;
	sf::Texture hero_textures[5];	
	sf::Texture face_texture;
	sf::Texture scull_texture;
	sf::Texture book_texture;

	sf::Texture table_texture;
	sf::Sprite table_sprite;
	sf::Texture wall_texture;
	sf::Sprite wall1_sprite;
	sf::Sprite wall2_sprite;
	sf::Sprite wall3_sprite;

	sf::RectangleShape cards[3];	
	sf::RectangleShape end_turn;

	sf::Font font;	

	sf::SoundBuffer punish_buff;
	sf::SoundBuffer reward_buff;
	sf::Sound punish_sound;
	sf::Sound reward_sound;

	Cell cells[7][7];
public:		
	int n;
	Hero* heroes;
	bool active;
	bool is_push;
	bool tp;
	int active_player;
	Hero* pushing;
	Hero* pushing2;
	Hero* tping;
	Card* active_card;
	int books;
	Game()
	{		
		v1_texture.loadFromFile("red.png");
		v2_texture.loadFromFile("green.png");
		v3_texture.loadFromFile("blue.png");
		v4_texture.loadFromFile("yellow.png");
		tp_texture.loadFromFile("tp.png");
		boss_texture.loadFromFile("boss.png");			
		hero_textures[0].loadFromFile("hero1.jpg");
		hero_textures[1].loadFromFile("hero2.jpg");
		hero_textures[2].loadFromFile("hero3.jpg");
		hero_textures[3].loadFromFile("hero4.jpg");
		hero_textures[4].loadFromFile("hero5.jpg");
		face_texture.loadFromFile("face.jpg");
		scull_texture.loadFromFile("scull.png");
		book_texture.loadFromFile("book.jpg");
		
		table_texture.loadFromFile("table.jpg");
		table_sprite.setTexture(table_texture);
		wall_texture.loadFromFile("wall.png");
		wall1_sprite.setTexture(wall_texture);
		wall2_sprite.setTexture(wall_texture);
		wall3_sprite.setTexture(wall_texture);

		font.loadFromFile("font.otf");		

		punish_buff.loadFromFile("punish.ogg");
		reward_buff.loadFromFile("reward.ogg");
		punish_sound.setBuffer(punish_buff);
		reward_sound.setBuffer(reward_buff);

		cells[0][0].value = cells[0][1].value = cells[0][4].value = cells[2][2].value = cells[2][6].value = cells[4][0].value = cells[4][1].value = cells[4][5].value = cells[6][2].value = cells[6][3].value = cells[6][6].value
			= 1;
		cells[0][2].value = cells[0][3].value = cells[2][0].value = cells[2][1].value = cells[2][4].value = cells[2][5].value = cells[4][3].value = cells[4][6].value = cells[6][0].value = cells[6][1].value = cells[6][4].value = cells[6][5].value
			= 2;
		cells[1][1].value = cells[1][2].value = cells[3][3].value = cells[3][4].value = cells[3][0].value = cells[5][1].value = cells[5][5].value = cells[5][6].value
			= 3;
		cells[1][0].value = cells[1][4].value = cells[3][1].value = cells[3][2].value = cells[3][5].value = cells[3][6].value = cells[5][0].value = cells[5][3].value
			= 4;
		cells[1][3].value = cells[2][3].value = cells[4][2].value = cells[4][4].value = cells[5][2].value = cells[5][4].value
			= 5;
		cells[0][5].value = cells[0][6].value = cells[1][5].value = cells[1][6].value
			= 0;

		cells[0][0].is_tp = cells[2][2].is_tp = cells[4][1].is_tp = cells[4][5].is_tp = cells[6][6].is_tp = true;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				cells[i][j].shape.setPosition(j * 150, i * 150);
			}
		}		

		n = 0;
		heroes = NULL;		
		active = false;
		is_push = false;
		tp = false;
		active_player = 0;
		pushing = NULL;
		pushing2 = NULL;
		tping = NULL;
		active_card = NULL;
		books = 15;				

		table_sprite.setPosition(cells[0][5].shape.getPosition());
		wall1_sprite.setPosition(cells[1][3].shape.getPosition());
		wall2_sprite.setPosition(cells[4][2].shape.getPosition());
		wall3_sprite.setPosition(cells[4][4].shape.getPosition());		

		for (int i = 0; i < 3; i++)
		{
			cards[i].setSize(sf::Vector2f(300, 300));
			cards[i].setPosition(1100, 100 + i * 330);
			cards[i].setOutlineColor(sf::Color::Black);
			cards[i].setOutlineThickness(-10);
		}

		end_turn.setSize(sf::Vector2f(400, 200));
		end_turn.setPosition(1500, 800);
		end_turn.setOutlineColor(sf::Color::Black);
		end_turn.setOutlineThickness(-10);
		end_turn.setFillColor(sf::Color::Transparent);		
	}
	void Init(int N)
	{
		n = N;
		heroes = new Hero[n + 1];		
		heroes[n].position1 = 0;
		heroes[n].position2 = 3;
		cells[0][3].hero = &heroes[n];
		heroes[n].shape.setTexture(&boss_texture);
		for (int i = 0; i < n; i++)
		{
			heroes[i].position1 = 6;
			heroes[i].position2 = i;
			cells[6][i].hero = &heroes[i];
			heroes[i].shape.setTexture(&hero_textures[i]);			
		}		

		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				heroes[i].cards[j].value1 = rand() % 4 + 1;
				heroes[i].cards[j].value2 = rand() % 4 + 1;
				heroes[i].cards[j].value3 = rand() % 4 + 1;
			}
		}
		
		is_push = false;
		tp = false;
		active_player = 0;
		pushing = NULL;
		pushing2 = NULL;
		tping = NULL;
		active_card = NULL;
		books = 15;		

		for (int i = 0; i < 3; i++)
		{
			cards[i].setOutlineColor(sf::Color::Black);
		}
	}	

	~Game()
	{
		delete[] heroes;		
	}

	void hero_move(int p1, int p2, Hero* h)
	{
		cells[h->position1][h->position2].hero = NULL;
		h->position1 = p1;
		h->position2 = p2;
		cells[p1][p2].hero = h;
	}

	bool can_move(int p1, int p2, Hero* h)
	{
		return ((h->position1 == p1 - 1 || h->position1 == p1 + 1) && h->position2 == p2) || ((h->position2 == p2 - 1 || h->position2 == p2 + 1) && h->position1 == p1);
	}

	bool check_tp()
	{
		if (cells[0][1].hero == NULL || cells[2][2].hero == NULL || cells[4][1].hero == NULL || cells[4][5].hero == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void punish(Hero* h)
	{
		punish_sound.play();
		hero_move(6, find_free(), h);
		h->penalty++;		
	}

	void prize(Hero* h)
	{
		reward_sound.play();
		srand(time(NULL));		
		hero_move(6, find_free(), h);
		h->score1++;
		h->score2 += rand() % 3 + 1;
		books--;
	}

	void teleportation(int p1, int p2, Hero* h)
	{
		if (cells[p1][p2].hero == NULL && cells[p1][p2].is_tp)
		{
			hero_move(p1, p2, h);
			tp = false;
			srand(time(NULL));
			switch (rand() % 3 + 1)
			{
			case 1: reward_sound.play(); break;
			case 2: 
				if (active_card->value3 == 1)
				{
					reward_sound.play();
				}
				else
				{
					punish_sound.play();
				}
				tping->penalty++; break;
			case 3: 
				reward_sound.play();
				tping->score1++;
				tping->score2 += rand() % 3 + 1;
				books--;
				break;
			}
			tping = NULL;
		}
	}

	void push(int p1, int p2)
	{		
		if (cells[p1][p2].value < 5 && cells[p1][p2].value > 0)
		{
			if (can_move(p1, p2, pushing)) 
			{
				if (cells[p1][p2].hero != NULL)
				{	
					if (cells[p1][p2].hero->position1 == heroes[n].position1 && cells[p1][p2].hero->position2 == heroes[n].position2)
					{
						pushing->shape.setOutlineColor(sf::Color::Transparent);
						pushing2->shape.setFillColor(sf::Color::White);
						punish(pushing);
						is_push = false;
						pushing = NULL;
						pushing2 = NULL;
					}
					else
					{
						Hero* temp = cells[p1][p2].hero;
						hero_move(p1, p2, pushing);
						cells[pushing2->position1][pushing2->position2].hero = pushing2;
						pushing->shape.setOutlineColor(sf::Color::Transparent);
						pushing2->shape.setFillColor(sf::Color::White);
						pushing2 = pushing;
						pushing = temp;
						pushing->shape.setOutlineColor(sf::Color::Red);
						pushing2->shape.setFillColor(sf::Color::Transparent);
					}
				}
				else
				{		
					pushing->shape.setOutlineColor(sf::Color::Transparent);
					pushing2->shape.setFillColor(sf::Color::White);		
					hero_move(p1, p2, pushing);
					cells[pushing2->position1][pushing2->position2].hero = pushing2;
					is_push = false;
					pushing = NULL;		
					pushing2 = NULL;					
				}							
			}
		}
	}

	void step_boss(int p1, int p2, int value)
	{
		if (active_card->value1 == value)
		{			
			if (can_move(p1, p2, &heroes[n]))
			{
				tping = NULL;
				tp = false;
				if (cells[p1][p2].hero != NULL)
				{					
					punish(cells[p1][p2].hero);
				}				
				hero_move(p1, p2, &heroes[n]);
				active_card->value1 = 0;

				if (cells[p1][p2].is_tp)
				{
					tp = check_tp();
					if (tp)
					{
						tping = &heroes[n];
					}
				}
			}			
		}

		if (active_card->value2 == value)
		{
			if(can_move(p1,p2, &heroes[n]))
			{
				tping = NULL;
				tp = false;
				if (cells[p1][p2].hero != NULL)
				{
					punish(cells[p1][p2].hero);
				}				
				hero_move(p1, p2, &heroes[n]);
				active_card->value2 = 0;	

				if (cells[p1][p2].is_tp)
				{
					tp = check_tp();
					if (tp)
					{
						tping = &heroes[n];
					}
				}
			}
		}
	}

	int find_free()
	{
		if (cells[6][0].hero == NULL)
		{
			return 0;
		}
		else if (cells[6][1].hero == NULL)
		{
			return 1;
		}
		else if (cells[6][2].hero == NULL)
		{
			return 2;
		}
		else if (cells[6][3].hero == NULL)
		{
			return 3;
		}
		else if (cells[6][4].hero == NULL)
		{
			return 4;
		}
		else if (cells[6][5].hero == NULL)
		{
			return 5;
		}
		else if (cells[6][6].hero == NULL)
		{
			return 6;
		}		
	}

	void step(int p1, int p2, int value)
	{
		if (value == 0)
		{
			if(can_move(p1,p2,&heroes[active_player]))
			{			
				prize(&heroes[active_player]);				
				active_card->value1 = 0;
				active_card->value2 = 0;
			}
		}

		if (active_card->value1 == value)
		{		
			if(can_move(p1,p2,&heroes[active_player]))
			{
				tping = NULL;
				tp = false;
				bool punished = false;
				if (cells[p1][p2].hero != NULL)
				{
					if (cells[p1][p2].hero->position1 == heroes[n].position1 && cells[p1][p2].hero->position2 == heroes[n].position2)
					{
						punished = true;
					}
					else
					{
						is_push = true;
						pushing = cells[p1][p2].hero;
						pushing2 = &heroes[active_player];
						pushing2->shape.setFillColor(sf::Color::Transparent);
						pushing->shape.setOutlineColor(sf::Color::Red);
					}
				}
				if (punished)
				{
					punish(&heroes[active_player]);
					active_card->value1 = 0;
					active_card->value2 = 0;
				}				
				else
				{					
					hero_move(p1, p2, &heroes[active_player]);
					active_card->value1 = 0;
				}

				if (cells[p1][p2].is_tp)
				{
					tp = check_tp();
					if (tp)
					{
						tping = &heroes[active_player];
					}
				}
			}
		}	

		if (active_card->value2 == value)
		{			
			if (can_move(p1, p2, &heroes[active_player])) 
			{
				tping = NULL;
				tp = false;
				bool punished = false;
				if (cells[p1][p2].hero != NULL)
				{
					if (cells[p1][p2].hero->position1 == heroes[n].position1 && cells[p1][p2].hero->position2 == heroes[n].position2)
					{
						punished = true;
					}
					else
					{
						is_push = true;
						pushing = cells[p1][p2].hero;
						pushing2 = &heroes[active_player];
						pushing2->shape.setFillColor(sf::Color::Transparent);
						pushing->shape.setOutlineColor(sf::Color::Red);						
					}
				}
				if (punished)
				{
					punish(&heroes[active_player]);
					active_card->value1 = 0;
					active_card->value2 = 0;
				}
				else
				{					
					hero_move(p1, p2, &heroes[active_player]);
					active_card->value2 = 0;
				}

				if (cells[p1][p2].is_tp)
				{
					tp = check_tp();
					if (tp)
					{
						tping = &heroes[active_player];
					}
				}
			}
		}
	}

	void game_choice(int x, int y)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (button_clicked(cells[i][j].shape, x, y))
				{
					if (tp)
					{
						teleportation(i, j, tping);
					}

					if (is_push)
					{
						push(i, j);
					}
					else if (active_card!=NULL)
					{
						if (active_card->value3 == 1)
						{
							step_boss(i, j, cells[i][j].value);
						}
						else
						{
							step(i, j, cells[i][j].value);
						}
					}
				}
			}
		}

		if (button_clicked(cards[0], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &heroes[active_player].cards[0];
				cards[0].setOutlineColor(sf::Color::Red);
			}			
		}
		else if (button_clicked(cards[1], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &heroes[active_player].cards[1];
				cards[1].setOutlineColor(sf::Color::Red);
			}
		}
		else if (button_clicked(cards[2], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &heroes[active_player].cards[2];
				cards[2].setOutlineColor(sf::Color::Red);
			}
		}
		else if (button_clicked(end_turn, x, y))
		{
			tping = NULL;
			tp = false;
			if (active_card != NULL)
			{
				active_card->new_card();				
				active_card = NULL;
				for (int i = 0; i < 3; i++)
				{
					cards[i].setOutlineColor(sf::Color::Black);
				}
			}
			if (active_player != n-1)
			{
				active_player++;
			}
			else
			{
				active_player = 0;
			}
		}	
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		draw_field(target, states);
		draw_heroes(target, states);
		draw_cards(target, states, active_player);
		draw_end(target, states);
	}

	void draw_field(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();		
		
		sf::RectangleShape value_shape(sf::Vector2f(37.5, 37.5));
		value_shape.setFillColor(grey);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				target.draw(cells[i][j].shape, states);
				if (cells[i][j].is_tp)
				{
					sf::RectangleShape tp_shape(sf::Vector2f(75, 75));
					tp_shape.setTexture(&tp_texture);
					tp_shape.setPosition(cells[i][j].shape.getPosition().x + 50, cells[i][j].shape.getPosition().y + 50);
					target.draw(tp_shape, states);
				}
				value_shape.setPosition(cells[i][j].shape.getPosition().x+10, cells[i][j].shape.getPosition().y + 10);
				if (cells[i][j].value == 1)
				{						
					value_shape.setTexture(&v1_texture);				
					target.draw(value_shape, states);
					
				}
				if (cells[i][j].value == 2)
				{
					value_shape.setTexture(&v2_texture);
					target.draw(value_shape, states);
				}
				if (cells[i][j].value == 3)
				{
					value_shape.setTexture(&v3_texture);
					target.draw(value_shape, states);
				}
				if (cells[i][j].value == 4)
				{
					value_shape.setTexture(&v4_texture);
					target.draw(value_shape, states);
				}
			}
		}	

		target.draw(table_sprite, states);
		target.draw(wall1_sprite, states);
		target.draw(wall2_sprite, states);
		target.draw(wall3_sprite, states);

		sf::Text text("", font, 55);
		text.setString(std::to_string(books));
		text.setPosition(100, 100);

	}

	void draw_heroes(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (int i = 0; i < n + 1; i++)
		{
			heroes[i].shape.setPosition(cells[heroes[i].position1][heroes[i].position2].shape.getPosition().x + 45, cells[heroes[i].position1][heroes[i].position2].shape.getPosition().y + 45);
			target.draw(heroes[i].shape, states);
		}
	}

	void draw_end(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		sf::Text text("End turn", font, 55);
		text.setFillColor(sf::Color::Black);
		sf::Text score("", font, 70);
		sf::Text penalty("", font, 70);
		score.setFillColor(sf::Color::Green);
		penalty.setFillColor(sf::Color::Red);
		score.setPosition(1650, 700);
		penalty.setPosition(1720, 700);

		sf::RectangleShape shape(end_turn);

		switch (active_player)
		{
		case 0: shape.setFillColor(sf::Color::Red); break;
		case 1: shape.setFillColor(sf::Color::Green); break;
		case 2: shape.setFillColor(sf::Color::Blue); break;
		case 3: shape.setFillColor(sf::Color::Yellow); break;
		case 4: shape.setFillColor(sf::Color::Magenta); break;
		default:break;
		}

		sf::RectangleShape book(sf::Vector2f(100, 150));
		book.setTexture(&book_texture);
		for (int i = 0; i < heroes[active_player].score1; i++)
		{
			book.setPosition(1500 + i * 30, 100);
			target.draw(book, states);
		}

		sf::Text amount("", font, 55);
		amount.setFillColor(sf::Color::White);
		amount.setPosition(980, 230);
		amount.setString(std::to_string(books));
		target.draw(amount);

		score.setString(std::to_string(heroes[active_player].score2));
		penalty.setString(std::to_string(heroes[active_player].penalty));
		target.draw(score, states);
		target.draw(penalty, states);

		text.setPosition(1600, 870);
		target.draw(shape, states);
		target.draw(text, states);
		target.draw(end_turn, states);
	}

	void draw_cards(sf::RenderTarget& target, sf::RenderStates states, int p) const
	{
		states.transform *= getTransform();	

		sf::RectangleShape value_shape(sf::Vector2f(75, 75));
		value_shape.setFillColor(sf::Color::White);
		for (int i = 0; i < 3; i++)
		{
			target.draw(cards[i], states);			

			value_shape.setPosition(cards[i].getPosition());
			if (heroes[p].cards[i].value3 == 1)
			{
				sf::RectangleShape shape(sf::Vector2f(150, 150));
				shape.setFillColor(sf::Color::White);
				shape.setPosition(cards[i].getPosition().x + 75, cards[i].getPosition().y + 75);
				shape.setTexture(&scull_texture);
				target.draw(shape, states);
			}
			else
			{
				sf::RectangleShape shape(sf::Vector2f(150, 150));
				shape.setFillColor(sf::Color::White);
				shape.setPosition(cards[i].getPosition().x + 75, cards[i].getPosition().y + 75);
				shape.setTexture(&face_texture);
				target.draw(shape, states);
			}
			if (heroes[p].cards[i].value1 == 1)
			{
				value_shape.setTexture(&v1_texture);
				target.draw(value_shape, states);

			}
			if (heroes[p].cards[i].value1 == 2)
			{
				value_shape.setTexture(&v2_texture);
				target.draw(value_shape, states);
			}
			if (heroes[p].cards[i].value1 == 3)
			{
				value_shape.setTexture(&v3_texture);
				target.draw(value_shape, states);
			}
			if (heroes[p].cards[i].value1 == 4)
			{
				value_shape.setTexture(&v4_texture);
				target.draw(value_shape, states);
			}

			value_shape.setPosition(cards[i].getPosition().x+225, cards[i].getPosition().y);
			if (heroes[p].cards[i].value2 == 1)
			{
				value_shape.setTexture(&v1_texture);
				target.draw(value_shape, states);

			}
			if (heroes[p].cards[i].value2 == 2)
			{
				value_shape.setTexture(&v2_texture);
				target.draw(value_shape, states);
			}
			if (heroes[p].cards[i].value2 == 3)
			{
				value_shape.setTexture(&v3_texture);
				target.draw(value_shape, states);
			}
			if (heroes[p].cards[i].value2 == 4)
			{
				value_shape.setTexture(&v4_texture);
				target.draw(value_shape, states);
			}
		}
	}
};
