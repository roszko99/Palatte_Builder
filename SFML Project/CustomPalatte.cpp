#include "CustomPalatte.h"
#include <cstdlib>



int CustomPalatte::recolorify(sf::RectangleShape *blocks[][BLOCKS_DIM], int key) {
	switch (key) {
	case recolor_keys::RAND:
		CustomPalatte::recolorify_rand(blocks);
		break;
	case recolor_keys::MONO:
		CustomPalatte::recolorify_monochrome(blocks);
		break;
	case recolor_keys::FLOOD:
		CustomPalatte::recolorify_flood(blocks, 0, 0, 1.);
		break;
	case recolor_keys::SIMPLE:
	{
		sf::Color primary = CustomPalatte::genColor();
		CustomPalatte::loadBlockPalatte(blocks, primary, CustomPalatte::analog(primary, 0.05), CustomPalatte::opposite(primary, 0.4));
	}
		break;
	case recolor_keys(TRI):
		break;
	}
	return 0;
}


int CustomPalatte::recolorify_rand(sf::RectangleShape *blocks[][BLOCKS_DIM]) {
	for (int i = 0; i < BLOCKS_DIM; ++i) {
		for (int j = 0; j < BLOCKS_DIM; ++j) {
			sf::RectangleShape *cur_block = blocks[i][j];
			uint8_t red = rand() % 256;
			uint8_t green = rand() % 256;
			uint8_t blue = rand() % 256;
			(*cur_block).setFillColor(sf::Color(red, green, blue));
		}
	}
	return 0;
}

int CustomPalatte::recolorify_flood(sf::RectangleShape *blocks[][BLOCKS_DIM], int i, int j, float strength) {
	
	return 0;
}


int CustomPalatte::recolorify_monochrome(sf::RectangleShape *blocks[][BLOCKS_DIM]) {
	sf::Color prime = CustomPalatte::genColor(100, 100, 100);
	sf::Color augment((255 - prime.r) / 5, (255 - prime.g) / 5, (255 - prime.b) /5);
	for (int i = 0; i < BLOCKS_DIM; ++i) {
		for (int j = 0; j < BLOCKS_DIM; ++j) {
			(*blocks[i][j]).setFillColor(sf::Color(prime.r + augment.r * (i / (BLOCKS_DIM /5)), prime.g + augment.g * (i / (BLOCKS_DIM /5)), prime.b + augment.b * (i / (BLOCKS_DIM /5))));
		}
	}
	return 0;
}


// TODO: deal with error cases
sf::Color CustomPalatte::genColor(uint8_t r_max, uint8_t g_max, uint8_t b_max, uint8_t alpha) {
	return sf::Color(rand() % r_max, rand() % g_max, rand() % b_max, alpha);
}


sf::Color CustomPalatte::opposite(sf::Color source, float randomness) {
	return sf::Color((255 - source.r) + randomness * (rand() % 512 - 256), (255 - source.g) + randomness * (rand() % 512 - 256), (255 - source.b) + randomness * (rand() % 512 - 256));
}

sf::Color CustomPalatte::analog(sf::Color source, float randomness) {
	uint8_t r = source.r;
	uint8_t g = source.g;
	uint8_t b = source.b;
	sf::Color result = sf::Color(r, g, b);
	uint8_t temp[] = { r, g, b };
	uint8_t min = 255;
	uint8_t max = 0;
	for (int i = 0; i < 3; ++i) {
		if (temp[i] < min) { min = temp[i]; }
		else if (temp[i] > max) { max = temp[i]; }
	}
	if (max == r) {
		result.g += r + randomness * (rand() % 512 - 256);
		result.g %= 256;
	}
	else if (max == g) {
		result.b += g + randomness * (rand() % 512 - 256);
		result.b %= 256;
	} 
	else {
		result.r += b + randomness * (rand() % 512 - 256);
		result.r %= 256;
	}
	return result;
}


int CustomPalatte::loadBlockPalatte(sf::RectangleShape *blocks[][BLOCKS_DIM], sf::Color primary, sf::Color secondary, sf::Color tertiary) {
	bool orient = rand() % 2;
	int break_1 = (rand() % 1 + 1) * BLOCKS_DIM / 4 + rand() % (BLOCKS_DIM / 6);
	int break_1_width = BLOCKS_DIM / 24 + rand() % (BLOCKS_DIM / 12);
	sf::Color brush;
	for (int i = 0; i < BLOCKS_DIM; ++i) {
		for (int j = 0; j < BLOCKS_DIM; ++j) {
			if ((orient == 1 && j <= break_1) || (orient == 0 && i <= break_1)) {
				brush = primary;
			}
			else if ((orient == 1 && j > break_1 && j < break_1 + break_1_width) || (orient == 0 && i > break_1 && i < break_1 + break_1_width)) {
				brush = secondary;
			}
			else {
				brush = tertiary;
			}
			(*blocks[i][j]).setFillColor(brush);
		}
	}
	return 0;
}


// NOT IMPLEMENTED
CustomPalatte::hsl * CustomPalatte::rgb_to_hsl(CustomPalatte::rgb *rgb) {
	uint8_t r = rgb->r;
	uint8_t g = rgb->g;
	uint8_t b = rgb->b;
	CustomPalatte::hsl *result = new CustomPalatte::hsl;
	double r_percent = r / (double) 255.;
	double g_percent = g / (double) 255.;
	double b_percent = b / (double) 255.;
	double temp[] = { r, g, b };
	double min = -1.;
	double max = -1.;
	for (int i = 0; i < 3; ++i) {
		if (temp[i] < min) { min = temp[i]; }
		else if (temp[i] > max) { max = temp[i]; }
	}
	result->luminance = (min + max) / 2.;
	result->saturation = (result->luminance < 0.5) ? (max - min) / (max + min) : (max - min) / (2. - max - min);
	if (max == r) {
		result->hue = (g - b) / (max - min);
	}
	else if (max = b) {
		result->hue = 2. + (b - r) / (max - min);
	}
	else {
		result->hue = 4. + (r - g) / (max - min);
	}
	return result;
}

// NOT IMPLEMENTED
CustomPalatte::rgb *hsl_to_rgb(CustomPalatte::hsl *hsl) {
	double hue = hsl->hue;
	double saturation = hsl->saturation;
	double luminance = hsl->luminance;
	double temp_1 = (luminance < 0.5) ? luminance * (1. + saturation) : luminance + saturation - luminance * saturation;
	double temp_2 = 2. * luminance - temp_1;
	hue = hue / 360.;
	double temp_r = hue + 0.333;
	double temp_g = hue;
	double temp_b = hue - 0.333;

	return NULL;
}
