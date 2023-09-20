#ifndef SCREEN_H
#define SCREEN_H
#include "SDL2/include/SDL.h"
#include <vector>

struct rgb {
	int r;
	int g;
	int b;
};


class Screen {
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> points;
	rgb backgroundColor;
	rgb drawColor;

	public:

	Screen(int width, int height, int renderScalePercent, rgb backgroundColor, rgb drawColor);

	// Adds a point to the screen's collection of points
	void pixel(float x, float y);

	// Colors the whole screen backgroundColor, then draws points in drawColor
	void show();

	// Wipes all of the points in the screen's collection of points
	void clear();

	// Check for input, like clicking the X button to close the window
	void input();



};

#endif