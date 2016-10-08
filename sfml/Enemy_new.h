#include "SFML\Graphics.hpp"
class Enemy :public player
{
private:
	float x, y;
public:
	Enemy(float X, float Y, int W, int H, bool KTO)
	{
		srand(time(NULL));
		life = true;
		x = X;
		y = Y;
		w = W;
		h = H;
		kto = KTO;
		health = 100;
		dir = 3;
		speed = 0.2;
		image.createMaskFromColor(Color(255, 255, 255));
		image.loadFromFile("images/tank_new1.png");
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void InteractionWithMap()
	{
		{
			if (x + w> 1280)
			{
				ChangeDir(dir);
				x = 1280 - w;
			}
			if (x < 0)
			{
				x = 0;
				ChangeDir(dir);
			}
			if (y + h > 768)
			{
				ChangeDir(dir);
				y = 768 - h;
			}
			if (y < 0)
			{
				y = 0;
				ChangeDir(dir);
			}
			sprite.setPosition(x, y);
		}
	}
	void  ChangeDir(int dirr)
	{
		dir = rand() % 4;
		if (dir == dirr) ChangeDir(dir);
	}
	bool  Strike(float X, float Y, int dirr)
	{
		if (abs((x - X < 200)) || abs((y - Y < 200)))
		{
			switch (dirr)
			{
			case 0:dir = 3; break;
			case 3:dir = 0; break;
			case 1:dir = 2; break;
			case 2:dir = 1; break;

			}
			return true;
		}
		return false;
	}
	void Update(float time)
	{
		switch (dir)
		{

		case 3:	sprite.setTextureRect(IntRect(0, 0, w, h)); break;
		case 0: {sprite.setTextureRect(IntRect(w + h + w, 0, h, w)); break; };
		case 2: {sprite.setTextureRect(IntRect(w, 0, h, w)); break; };
		case 1: {sprite.setTextureRect(IntRect(w + h, 0, w, h)); break; };
		}

		switch (dir)
		{
		case 2: { dx = speed; dy = 0; break; }
		case 1: {dx = -speed; dy = 0; break; }
		case 0: {dx = 0; dy = speed;  break; }
		case 3: {dx = 0; dy = -speed;  break; }
		}
		{
			x += dx*time;
			y += dy*time;
		}
		if (x + w> 1280)
		{
			ChangeDir(dir);
			x = 1280 - w;
		}
		if (x < 0)
		{
			x = 0;
			ChangeDir(dir);
		}
		if (y + h > 768)
		{
			ChangeDir(dir);
			y = 768 - h;
		}
		if (y < 0)
		{
			y = 0;
			ChangeDir(dir);
		}
		sprite.setPosition(x, y);
		if (health <= 0)
		{
			life = false;
			health = 0;
		}
	}
	~Enemy()
	{

	}
	void InteractionWithTank_(float X, float Y, float time)
	{
		InteractionWithTank(X, Y, time);
		ChangeDir(dir);
	}
};