#include "palwinutil.h"



PalwinUtil::PalwinUtil(sf::RenderWindow *win, sf::RectangleShape **blocks) {
	window = win;
	blocks_ptr = blocks;
	recolorify_brush = CustomPalatte::SIMPLE;

}

PalwinUtil::~PalwinUtil() {

}


int PalwinUtil::handleMouseEvent(sf::Event event) {
	if (event.mouseButton.button == sf::Mouse::Left) {
		//CustomPalatte::recolorify(
	}
	else if (event.mouseButton.button == sf::Mouse::Right) {

	}
	return 0;
}