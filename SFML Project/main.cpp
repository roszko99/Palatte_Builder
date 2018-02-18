#include "cuspal.h"

int initBlocks(sf::RectangleShape *blocks[][BLOCKS_DIM]);
int drawBlocks(sf::RenderWindow *window, sf::RectangleShape* blocks[][BLOCKS_DIM]);
int freeBlocks(sf::RectangleShape *blocks[][BLOCKS_DIM]);

int main()
{
	sf::RenderWindow window(sf::VideoMode(BLOCKS_DIM * BLOCK_WIDTH, BLOCKS_DIM * BLOCK_WIDTH), "palatte_producer");
	//PalwinUtil inputHandler(&window);
	sf::RectangleShape *blocks[BLOCKS_DIM][BLOCKS_DIM];

	initBlocks(blocks);

	//	MAIN LOOP
	while (window.isOpen())
	{
		//	HANDLE EVENTS
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::MouseButtonPressed:			// On click:
				CustomPalatte::recolorify(blocks, CustomPalatte::SIMPLE);
				break;
			case sf::Event::Closed:						// On close:
				window.close();							// Close window
				break;
			}
		}

		//	DRAW OBJECTS
		window.clear(sf::Color::Black);
		for (int i = 0; i < BLOCKS_DIM; ++i) {
			for (int j = 0; j < BLOCKS_DIM; ++j) {
				window.draw(*blocks[i][j]);
			}
		}

		//	DISPLAY
		window.display();
	}

	freeBlocks(blocks);
	return 0;
}


int initBlocks(sf::RectangleShape* blocks[][BLOCKS_DIM]) {
	for (int i = 0; i < BLOCKS_DIM; ++i) {
		for (int j = 0; j < BLOCKS_DIM; ++j) {
			sf::RectangleShape *cur_block = blocks[i][j] = new sf::RectangleShape(sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH));		// Dynamically allocate array
			(*cur_block).move(BLOCK_WIDTH * i, BLOCK_WIDTH * j);
			(*cur_block).setFillColor(sf::Color::Transparent);
			//(*cur_block).setOutlineColor(sf::Color::White);
			//(*cur_block).setOutlineThickness(-1);
		}
	}
	return 0;
}


int freeBlocks(sf::RectangleShape* blocks[][BLOCKS_DIM]) {
	for (int i = 0; i < BLOCKS_DIM; ++i) {
		for (int j = 0; j < BLOCKS_DIM; ++j) {
			delete blocks[i][j];
		}
	}
	return 0;
}