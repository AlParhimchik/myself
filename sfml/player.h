#include <SFML/Graphics.hpp>

using namespace sf;

class player
{
private:
	float x, y, runtime;
public:
	int w, h;
	bool kto;
	static int play;
	float speed, dx = 0, dy = 0;
	int health,dir = 0,hit;
	bool life;
	Image image;
	Texture texture;
	Sprite sprite;
	player()
	{

	}
	player( float X, float Y, int W, int H,bool KTO)
	{
		runtime = speed=0;
		health = 100;
		kto = KTO;
		life = 1;
		w = W;
		h = H;
		x = X;
		y = Y;
		hit = 0;
		image.createMaskFromColor(Color(255,255,255));
		image.loadFromFile("images/tank_new1.png");
		image.createMaskFromColor(Color(255, 255, 255)); 
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dir = 3;
	}
	void update(float time);
	inline float GetPlayerCoordinateX()
	{
		return x;
	}
	inline float GetPlayerCoordinateY()
	{
		return y;
	}
	void SetKeyboard(int, float&);
	void InteractionWithMap(void);
	void InteractionWithTank(float,float,float);
};
int player::play = 0;
void player::InteractionWithTank(float X,float Y,float time)
{
	switch (dir)
	{
	case 0:
	{
		if ((x >= X && x <= X + w || x + w >= X && x + w <= X + w) && (y + h >= Y && y + h <= Y + h))
		{
			hit = 1;
		}
		break;
	}

	case 2:
	{
		if ((x + w > X && x + w < X + w) && (y > Y && y < Y + h || y + h > Y && y + h < Y + h))
		{
			hit = 1;
		}
		break;
	}
	case 1:
	{
		if ((x > X && x < X + w) && (y >= Y && y <= Y + h || y + h >= Y && y + h <= Y + h))
		{
			hit = 1;
		}
		break;
	}
	case 3:
	{
		if ((x >= X && x <= X + w || x + w >= X && x + w <= X + w) && (y > Y && y < Y + h))
		{
			hit = 1;
		}
		break;
	}
	}
	if (hit == 1)
	{
		x -= dx*time;
		y -= dy*time;
		hit =0;
	}
	InteractionWithMap();
}
void player::SetKeyboard(int key, float &time)
{ 
	dir = key;
	speed = 0.1;
	switch (dir)
		{
			
		case 3:	sprite.setTextureRect(IntRect(0,0,w,h)); break;
		case 0: {sprite.setTextureRect(IntRect(w+h+w,0, h, w)); break; };
		case 2: {sprite.setTextureRect(IntRect(w, 0, h, w)); break; };
		case 1:{sprite.setTextureRect(IntRect(w+h, 0, w, h)); break; };
		}
}
void player::update(float time)
{
	switch (dir)
	{
	case 2: { dx = speed; dy = 0; break; }
	case 1: {dx = -speed; dy = 0; break; }
	case 0: {dx = 0; dy = speed;  break; }
	case 3: {dx = 0; dy = -speed;  break; }
	}
	//if (hit != dir)
	{
		x += dx*time;
		y += dy*time;
	}

	speed = 0;
	if (health <= 0)
	{
		life = false;
		health = 0;
	}
}
void player::InteractionWithMap(void)
{
    if (x > 1280-w) x = 1280-w;
	if (x < 0) x = 0;
	if (y > 768-h) y =768-h;
	if (y < 0) y =0;
	sprite.setPosition(x, y);
}
