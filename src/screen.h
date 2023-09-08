#ifndef SCREEN_H
#define SCREEN_H
#include "SDL2/include/SDL.h"
#include <vector>

class Screen {
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> points;

	public:

		
	Screen(int width, int height, float renderScale);

	/*Adds a point to the screen's collection of points */
	void pixel(float x, float y);

	/*Colors the whole screen black, then draws all of the points in white*/
	void show();

	/*Wipes all of the points in the screen's collection of points*/
	void clear();

	void input();



};

#endif