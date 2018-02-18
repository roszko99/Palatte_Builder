#pragma once
#include <SFML/Graphics.hpp>
#include "CustomPalatte.h"



class PalwinUtil 
{
public:
	PalwinUtil(sf::RenderWindow *window, sf::RectangleShape **blocks);
	~PalwinUtil();
	int handleMouseEvent(sf::Event event);
private:
	sf::RenderWindow *window;
	sf::RectangleShape **blocks_ptr;
	int recolorify_brush;
};