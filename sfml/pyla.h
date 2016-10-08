#include <SFML/Graphics.hpp>
using namespace sf;
class pyla
{
public:
	float x, y,speedx,speedy,h,w;
	float dx = 0, dy = 0,speed;
	pyla *adr;
	 Image image;
	 Texture texture;
	 Sprite sprite;
	String string;
	bool who;
	int dir;
	pyla()
	{
		image.loadFromFile("images/bullet.png");
		image.createMaskFromColor(Color(255,255,255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		speed = 0.5;
	}
	bool Update(float time);
	bool InteractionWithMap();
	bool InteractionWithTank(player &);
	bool InteractionWithEnemy(enemy &);
	
};

pyla * BoOm(int dir,pyla *t,float x,float y,bool WHO)
{
		pyla *b = new pyla;
		b->adr = t;
		t = b;
		t->dir = dir;
		t->who = WHO;
		switch (dir)
		{
		case 3: {t->h = 26; t->w = 12; t->sprite.setTextureRect(IntRect(0, 0, t->w, t->h)); t->x = x + 34; t->y = y-17; break; };
		case 2: { t->h = 12; t->w = 26; t->sprite.setTextureRect(IntRect(24, 0, t->w, t->h)); t->x = x +74; t->y = y + 37; break; };
		case 1: {t->h = 12; t->w = 26; t->sprite.setTextureRect(IntRect(24, 12, t->w, t->h)); t->x = x-13 ; t->y = y +37; break; };
		case 0: {t->h = 26; t->w = 12; t->sprite.setTextureRect(IntRect(12, 0, t->w, t->h)); t->x = x + 34; t->y=y + 79; break; };
		}
		
			return t;
}
bool pyla::Update(float time)
{
	switch (dir)
	{
		case 2: { dx = speed; dy = 0; break; }
		case 1: {dx = -speed; dy = 0; break; }
		case 0: {dx = 0; dy = speed;  break; }
		case 3: {dx = 0; dy = -speed;  break; }
	}
	x += dx*time;
	y += dy*time;
	sprite.setPosition(x, y);
	return InteractionWithMap();
}
pyla *update(pyla *t,float time)
{
	while (true)
	{
		if (t == NULL) return NULL;
		pyla *b = t->adr;
		bool o=t->Update(time);
		if (o)
		{
			delete t;
			t = b;
		}
		else break;
			
	}
	pyla *b = t;
	while (t->adr != NULL)
	{
		pyla *k = t->adr;
		bool o=k->Update(time);
		if (o)
		{
			t->adr = k->adr;
			delete k;
		}
		else t = t->adr;
	}
	return b;

}
bool pyla::InteractionWithMap()
{

	if (x > 1280 || x < 0 || y > 768 || (y < 0)) return 1;
	sprite.setPosition(x, y);
	return 0;
}
pyla* IntegrationWithTank(pyla*t, player &tank)
{
	while (true)
	{
		if (t == NULL) return NULL;
		pyla *b = t->adr;
		bool o = t->InteractionWithTank(tank);
		if (o )
		{
			delete t;
			t = b;
		}
		else break;

	}
	pyla *b = t;
	while (t->adr != NULL)
	{
		pyla *k = t->adr;
		bool o = k->InteractionWithTank(tank);
		if (o)
		{
			t->adr = k->adr;
			delete k;
		}
		else t = t->adr;
	}
	return b;
}
bool pyla::InteractionWithTank(player &tank)
{
	
	if (who == tank.kto) return false;
	float px, py, tx, ty;
	switch (dir)
	{
		case 0:
		{
			if ((x > tank.GetPlayerCoordinateX() && x < tank.GetPlayerCoordinateX() + tank.w || x + w >= tank.GetPlayerCoordinateX() && x + tank.w <= tank.GetPlayerCoordinateX() + tank.w) && (y + h>= tank.GetPlayerCoordinateY() && y + h <= tank.GetPlayerCoordinateY() + tank.h))
			{
				tank.health -= 50;
				return 1;
			}
			break;
		}

		case 2:
		{
			if ((x + w > tank.GetPlayerCoordinateX() && x + w < tank.GetPlayerCoordinateX() + tank.w) && (y > tank.GetPlayerCoordinateY() && y < tank.GetPlayerCoordinateY() + tank.h || y + h > tank.GetPlayerCoordinateY() && y + h < tank.GetPlayerCoordinateY() + tank.h))
			{
				tank.health -= 50;
				return 1;
			}
			break;
		}
		case 1:
		{
			if ((x > tank.GetPlayerCoordinateX() && x < tank.GetPlayerCoordinateX() + tank.w) && (y >= tank.GetPlayerCoordinateY() && y <= tank.GetPlayerCoordinateY() + tank.h || y + h >= tank.GetPlayerCoordinateY() && y + h <= tank.GetPlayerCoordinateY() + tank.h))
			{
				tank.health -= 50;
				return 1;
			}
			break;
		}
		case 3:
		{
			if ((x >= tank.GetPlayerCoordinateX() && x <= tank.GetPlayerCoordinateX() + tank.w || x + w >= tank.GetPlayerCoordinateX() && x + w <= tank.GetPlayerCoordinateX() + tank.w) && (y > tank.GetPlayerCoordinateY() && y < tank.GetPlayerCoordinateY() + tank.h))
			{
				tank.health -= 50;
				return 1;
			}
			break;
		}
	}
	
	return 0;
}
pyla* IntegrationWithEnemy(pyla*t, enemy &tank)
{
	while (true)
	{
		if (t == NULL) return NULL;
		pyla *b = t->adr;
		bool o = t->InteractionWithEnemy(tank);
		if (o)
		{
			delete t;
			t = b;
		}
		else break;

	}
	pyla *b = t;
	while (t->adr != NULL)
	{
		pyla *k = t->adr;
		bool o = k->InteractionWithEnemy(tank);
		if (o)
		{
			t->adr = k->adr;
			delete k;
		}
		else t = t->adr;
	}
	return b;
}
bool pyla::InteractionWithEnemy(enemy &tank)
{
	if (who == tank.kto) return false;
	float px, py, tx, ty;
	switch (dir)
	{
	case 0:
	{
		if ((x > tank.GetPlayerCoordinateX() && x < tank.GetPlayerCoordinateX() + tank.w || x + w >= tank.GetPlayerCoordinateX() && x + tank.w <= tank.GetPlayerCoordinateX() + tank.w) && (y + h >= tank.GetPlayerCoordinateY() && y + h <= tank.GetPlayerCoordinateY() + tank.h))
		{
			tank.health -= 50;
			return 1;
		}
		break;
	}

	case 2:
	{
		if ((x + w > tank.GetPlayerCoordinateX() && x + w < tank.GetPlayerCoordinateX() + tank.w) && (y > tank.GetPlayerCoordinateY() && y < tank.GetPlayerCoordinateY() + tank.h || y + h > tank.GetPlayerCoordinateY() && y + h < tank.GetPlayerCoordinateY() + tank.h))
		{
			tank.health -= 50;
			return 1;
		}
		break;
	}
	case 1:
	{
		if ((x > tank.GetPlayerCoordinateX() && x < tank.GetPlayerCoordinateX() + tank.w) && (y >= tank.GetPlayerCoordinateY() && y <= tank.GetPlayerCoordinateY() + tank.h || y + h >= tank.GetPlayerCoordinateY() && y + h <= tank.GetPlayerCoordinateY() + tank.h))
		{
			tank.health -= 50;
			return 1;
		}
		break;
	}
	case 3:
	{
		if ((x >= tank.GetPlayerCoordinateX() && x <= tank.GetPlayerCoordinateX() + tank.w || x + w >= tank.GetPlayerCoordinateX() && x + w <= tank.GetPlayerCoordinateX() + tank.w) && (y > tank.GetPlayerCoordinateY() && y < tank.GetPlayerCoordinateY() + tank.h))
		{
			tank.health -= 50;
			return 1;
		}
		break;
	}
	}

	return 0;
}