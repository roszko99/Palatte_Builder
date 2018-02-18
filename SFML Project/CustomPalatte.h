#pragma once
#include <SFML/Graphics.hpp>

#define BLOCKS_DIM 100
#define BLOCK_WIDTH 10

class CustomPalatte
{
public:
	static enum recolor_keys {
		RAND, MONO, FLOOD, SIMPLE, TRI
	};
	typedef struct {
		int hue;
		double saturation;
		double luminance;
	} hsl;
	typedef struct {
		uint8_t r;
		uint8_t g;
		uint8_t b;
	} rgb;
	static int recolorify(sf::RectangleShape *blocks[][BLOCKS_DIM], int key);
	static sf::Color genColor(uint8_t r_max = 255, uint8_t g_max = 255, uint8_t b_max = 255, uint8_t alpha = ((uint8_t) 255));
	static sf::Color opposite(sf::Color source, float randomness = 0.);
	static sf::Color analog(sf::Color source, float randomness = 0.);
	static int loadBlockPalatte(sf::RectangleShape *blocks[][BLOCKS_DIM], sf::Color primary, sf::Color secondary, sf::Color tertiary);

private:
	static int recolorify_rand(sf::RectangleShape *blocks[][BLOCKS_DIM]);
	static int recolorify_flood(sf::RectangleShape *blocks[][BLOCKS_DIM], int i, int j, float strength);
	static int recolorify_monochrome(sf::RectangleShape *blocks[][BLOCKS_DIM]);
	static hsl *rgb_to_hsl(rgb *rgb);
	static rgb *hsl_to_rgb(hsl *hsl);
};

