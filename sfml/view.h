#include <SFML/Graphics.hpp>
using namespace sf;
View view;
View GetPlayerCoodrinateForView(float x, float y)
{
	if (x < 320) x = 320;
	if (y < 240) y = 240;
	if (y > 554) y = 554;
	view.setCenter(640 , 400);
	return view;
}
