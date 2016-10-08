#include <SFML\Graphics.hpp>
#include "Backend.h"
#include <fstream>
using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(860, 480), "Helper");
	Event event;
	Spisok_object *obj = NULL;
	while (window.isOpen())
	{
		window.clear();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ButtonAdd buttonadd(100,100,300,100,"images/button_add.png");
		buttonadd.interaction(Mouse::getPosition().x,Mouse::getPosition().y,window.getPosition().x,window.getPosition().y);
		object_push(&obj,&buttonadd);
		draw_objects(window,obj);
		while (true)
		{

			window.waitEvent(event);
			buttonadd.read();
			if (event.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) break;
			}
		}
			//Keyboard::Key a=Keyboard::Key::B;
			//if(Keyboard::Key a=Event::KeyEvent::code);	
		//string str1 = str;
		//cout << *a << endl;
		window.display();

	}
}