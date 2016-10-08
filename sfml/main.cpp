#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "map.h"
#include "player.h"
#include "view.h"
#include "pyla.h";
#include "menu.h";
#include "Enemy_new.h"
using namespace sf;

int main()
{
	//////////создание текстов//////////
	Font font;
	Enemy t;
	font.loadFromFile("CyrilicOld.ttf");
	Text TankText1("", font, 20), TankText2("", font, 20), textLifeSeconds("", font, 18);
	TankText1.setColor(Color::Blue);
	TankText1.setStyle(Text::Bold);
	TankText2.setColor(Color::Blue);
	TankText2.setStyle(Text::Bold);
	textLifeSeconds.setColor(Color::Red);
	textLifeSeconds.setStyle(Text::Bold);
	//////создание карты/////////

	Sprite s_map;
	Image i_map;																																																											
	i_map.loadFromFile("images/map1.png");
	//i_map.createMaskFromColor(Color(106, 118, 82));

	Texture t_map;
	t_map.loadFromImage(i_map);

	s_map.setTexture(t_map);

	//////////////
	Clock clock, TimeForLife, TimeForGame;
	float LifeTime = 0;

	RenderWindow window(sf::VideoMode(860, 480), "sanzoyz");
	view.reset(FloatRect(0, 0, 1280, 768));
	sf::Event event;
	bool GameMode;
	while (true)
	{
		
		CreateMenu();
		while (true)
		{
			float x = window.getPosition().x, y = window.getPosition().y+30, kx = 860. / 1280,ky=480./768;

			window.draw(sprt);
			window.setView(view);
																																																																																																										
			if (Mouse::getPosition().x- x<1061*kx && Mouse::getPosition().x- x>261*kx && Mouse::getPosition().y-y <124*ky && Mouse::getPosition().y -y> 56*ky)
			{
				CreateMenuForNewGame(1);
				window.draw(sprt1);
			}
			else
			if (Mouse::getPosition().x - x < 910*kx && Mouse::getPosition().x- x>385*kx && Mouse::getPosition().y - y<353*ky && Mouse::getPosition().y - y> 280*ky)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					GameMode = false;
					break;
				}
				CreateMenuForNewGame(2);
				window.draw(sprt1);
			}
			else
				if (Mouse::getPosition().x - x < 914*kx && Mouse::getPosition().x - x>377*kx && Mouse::getPosition().y - y <468*ky && Mouse::getPosition().y - y> 404*ky)
				{
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						GameMode = true;
						break;
					}
					CreateMenuForNewGame(3);
					window.draw(sprt1);
				}
				else
			if (Mouse::getPosition().x - x< 830*kx && Mouse::getPosition().x - x>440*kx && Mouse::getPosition().y - y <600*ky && Mouse::getPosition().y - y> 529*ky)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					return 0;
				}
				CreateMenuForNewGame(4);
				window.draw(sprt1);
			}
			else window.draw(sprt);
			window.display();
			window.clear();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				return 0;
			}
		}
		player tank( 100, 100, 74, 74, 1);
		player tank2(1000, 700, 74, 74, 0);

		Enemy enemy(1000, 700, 74, 74,0);

		pyla *pop = NULL;			

		float game_time = TimeForGame.getElapsedTime().asSeconds();
		float PylalTank1 = 0, PylaTank2 = 0;
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds(), speedx, speedy;
			std::ostringstream HealthTank1, HealthTank2;
			game_time = TimeForGame.getElapsedTime().asSeconds();
			clock.restart();
			time /= 800;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			//////////////////работа к клавиарутой и мышью///////////

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if (GameMode) if (tank2.life)
			{
				if (Keyboard::isKeyPressed(Keyboard::Numpad4))	tank2.SetKeyboard(1, time);
				if (Keyboard::isKeyPressed(Keyboard::Numpad6)) tank2.SetKeyboard(2, time);
				if (Keyboard::isKeyPressed(Keyboard::Numpad8)) tank2.SetKeyboard(3, time);
				if (Keyboard::isKeyPressed(Keyboard::Numpad5)) tank2.SetKeyboard(0, time);
				if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::RShift))

				{
					if (game_time - PylaTank2 > 0.5)
					{
						PylaTank2 = game_time;
						pop = BoOm(tank2.dir,pop, tank2.GetPlayerCoordinateX(),tank2.GetPlayerCoordinateY(), false);
					}
				}
			}
			if (tank.life)
			{
				if (Keyboard::isKeyPressed(Keyboard::W)) tank.SetKeyboard(3, time);
				if (Keyboard::isKeyPressed(Keyboard::S)) tank.SetKeyboard(0, time);
				if (Keyboard::isKeyPressed(Keyboard::A)) tank.SetKeyboard(1, time);
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					tank.SetKeyboard(2, time);
				}
				if (Keyboard::isKeyPressed(Keyboard::LShift))
				{
					if (game_time - PylalTank1 > 0.5)
					{
						PylalTank1 = game_time;
					 pop = BoOm(tank.dir, pop, tank.GetPlayerCoordinateX(), tank.GetPlayerCoordinateY(), true);
					}
				}

			}
			if (!GameMode && Enemy.life)
				if (game_time - PylaTank2 > 0.5)
				{
					if (Enemy.Strike(tank.GetPlayerCoordinateX(), tank.GetPlayerCoordinateY(),tank.dir))
					{
						PylaTank2 = game_time;
						pop = BoOm(Enemy.dir, pop, Enemy.GetPlayerCoordinateX(), Enemy.GetPlayerCoordinateY(), false);
					}
				}
			window.clear();
			pop = update(pop, time);
			if (GameMode) tank2.update(time);

			tank.update(time);
			if (GameMode)
			{
				tank.InteractionWithTank(tank2.GetPlayerCoordinateX(),tank2.GetPlayerCoordinateY, time);
				tank2.InteractionWithTank(tank.GetPlayerCoordinateX(), tank.GetPlayerCoordinateY, time);
				pop = IntegrationWithTank(pop, tank);
				pop = IntegrationWithTank(pop, tank2);
			}
			else
			{
				tank.InteractionWithEnemy(Enemy,time);
				Enemy.InteractionWithTank(tank.GetPlayerCoordinateX(),tank.GetPlayerCoordinateY(),time);
				pop = IntegrationWithTank(pop, tank);
				pop = IntegrationWithEnemy(pop, Enemy);
			}

			window.setView(view);
			if (tank.life)
			{
				HealthTank1 << tank.health;
				TankText1.setString("health: " + HealthTank1.str());
				TankText1.setPosition(10, 15);
			}
			if (GameMode) if (tank2.life)
			{
				HealthTank2 << tank2.health;
				TankText2.setString("health: " + HealthTank2.str());
				TankText2.setPosition(1150, 15);
			}
			if (!GameMode) if (Enemy.life)
			{
				HealthTank2 << Enemy.health;
				TankText2.setString("health: " + HealthTank2.str());
				TankText2.setPosition(1150, 15);
			}
			/////////////карта/////////////////	
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == '0' || TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(0, 0, 128, 128));
					if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(128, 0, 128, 128));
					//if (TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
					s_map.setPosition(j * 128, i * 128);
					window.draw(s_map);
				}
			////////////

			if (tank.life) window.draw(TankText1);
			if (tank2.life && Enemy.life) window.draw(TankText2);
			
			window.draw(tank.sprite);
			if (GameMode) window.draw(tank2.sprite); else
			{
				Enemy.Update(time);
				if (Enemy.life) window.draw(Enemy.sprite);
			}
			pyla *b = pop;
			while (b != NULL)
			{
				window.draw(b->sprite);
				b = b->adr;
			}
			if (!tank.life || !tank2.life || !Enemy.life)
			{
				Text TextEndOfGame("                      Game Over\nPress BackSpace to enter menu..",font, 25);
				TextEndOfGame.setPosition(500, 300);
				TextEndOfGame.setColor(Color::Blue);
				window.draw(TextEndOfGame);
				if (Keyboard::isKeyPressed(Keyboard::BackSpace)) break;
			}

			window.display();		
		}
	}

	return 0;
} 



