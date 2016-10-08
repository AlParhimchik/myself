#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Object;
class Spisok_object
{
public:
	Object *obj;
	Spisok_object *left;
	Spisok_object *right;
};
class Object:public InputStream
{
public:virtual void draw(RenderWindow &window)
	{
	}
};
class ButtonAdd:public Object
{
private:
	float x, y, w, h;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
public:
	ButtonAdd(float X,float Y,float W,float H,String str):x(X),y(Y),w(W),h(H)
	{
		texture.loadFromFile(str);
		sprite.setTexture(texture);
		//rectangle.setSize(sf::Vector2f(w, h));
		//rectangle.setOutlineColor(sf::Color::Red);
		//rectangle.setOutlineThickness(5);
		sprite.setPosition(x, y);
	}
	void draw(RenderWindow &window)
	{
		window.draw(sprite);
	}
	void interaction(float m_x,float m_y,float w_x,float w_y)
	{
		if (FloatRect(x+w_x, y+w_y, w, h).contains(m_x, m_y) &&Mouse::isButtonPressed(Mouse::Left)  ) std::cout << "idite naxer" << std::endl;
	}
	Int64 read(void* data, Int64 size)
	{
		
	}
	~ButtonAdd()
	{
	}
};
void draw_objects(RenderWindow &window,Spisok_object* object)
{
	while (object != NULL)
	{
		object->obj->draw(window);
		object = object->left;
	}
}
void object_push(Spisok_object **object,Object *obj)
{
	Spisok_object *t = new Spisok_object;
	t->obj =obj;
	t->right = NULL;
	t->left = *object;
	if (*object != NULL) (*object)->right = t;
	(*object) = t;
}