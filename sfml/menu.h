#include <SFML/Graphics.hpp>
Image img, img1, img2;
Texture txtr, txtr1;
Sprite sprt, sprt1;

void CreateMenu()
{
	img.loadFromFile("images/menu_1.png");
	txtr.loadFromImage(img);
	sprt.setTexture(txtr);
	sprt.setPosition(0, 0);
}
void CreateMenuForNewGame(int a)
{
	if (a==1)
	{
		img1.loadFromFile("images/menu_2.png");
		txtr1.loadFromImage(img1);
		sprt1.setTexture(txtr1);
		//sprt1.setPosition(300, 100);

	}
	if (a==2)
	{
		img1.loadFromFile("images/menu_3.png");
		txtr1.loadFromImage(img1);
		sprt1.setTexture(txtr1);

	}
	if (a == 3)
	{
		img1.loadFromFile("images/menu_4.png");
		txtr1.loadFromImage(img1);
		sprt1.setTexture(txtr1);

	}
	if (a == 4)
	{
		img1.loadFromFile("images/menu_5.png");
		txtr1.loadFromImage(img1);
		sprt1.setTexture(txtr1);

	}

}
