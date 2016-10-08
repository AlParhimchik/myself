#include <SFML/Graphics.hpp>
using namespace sf;
class Ball1
{
public:
	float x, y;
	Ball1(float X, float Y)
	{
		x = X;
		y = Y;
	}
};
class Speed
{
public:
	float speedx, speedy;
	Speed(float Speedx, float Speedy)
	{
		speedx = Speedx;
		speedy = Speedy;
	}
};
class Ball
{
private:
	float x, y, speedx, speedy;
public:
	CircleShape circle;
	Ball(int X,int Y)
	{
		x = X;
		y = Y;
		speedx = 0.2;
		speedy = 0.1;
		circle.setRadius(10);
		circle.setOutlineColor(sf::Color::White);
		//circle.setOutlineThickness(5);
		circle.setPosition(1, 1);
	}
	void Moution()
	{
		x += speedx;
		y += speedy;
	}
	Ball1 GetCoordinate()
	{
		Ball1 ball1(x,y);
		return ball1;
	}
	Speed GetSpeed()
	{
		Speed spd(speedx, speedy);
		return spd;
	}
	void InteractionWithMap()
	{
		if (x +2*circle.getRadius() > 840 || x < 0)
		{
			speedx = -speedx;
			Moution();
		}
			if ( y +2*circle.getRadius()> 680 || y < 0) speedy = -speedy;
			{
				Moution();
			}
	}

	void Update(RenderWindow &window)
	{
		Moution();
		InteractionWithMap();
		circle.setPosition(x, y);
		window.draw(circle);
	}
	
};
class Map
{
private:
	int SIZE_H, SIZE_W;
	int **map;
	Texture texture;
	Sprite sprite;
public:
	Map(int size_h,int size_w)
	{
		int i, j;
		SIZE_H = size_h;
		SIZE_W = size_w;
		texture.loadFromFile("images/map_tile.png");
		sprite.setTexture(texture);
		map = new int*[SIZE_H];
		for (i = 0; i < SIZE_H; i++)
		{
			map[i] = new int[SIZE_W];
			for (j = 0; j < SIZE_W; j++)
			{
				if (i == 0 || i == SIZE_H-1 || j == 0 || j == SIZE_W-1) map[i][j] = 1; else map[i][j] = 0;
			}
		}
	}
	void Update(RenderWindow &window)
	{
		int i, j;
		for (i = 0; i < SIZE_H; i++)
			for (j = 0; j < SIZE_W; j++)
			{
				if (map[i][j] == 1) sprite.setTextureRect(IntRect(0, 0, 20, 20));
				else				sprite.setTextureRect(IntRect(20, 0, 20, 20));
				sprite.setPosition(i * 20, j * 20);
				window.draw(sprite);
			}
	}
};

int main()
{
	Event event;
	RenderWindow window(VideoMode(840, 680), "sanzoyz");	
	Ball ball(100,100);
	Map map(42,34);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ball.Update(window);
		window.clear();
		map.Update(window);
		ball.Update(window);
		window.display();

	
	}
	return 0;
}