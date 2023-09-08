#include "screen.h"

Screen::Screen(int width, int height, float renderScale) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, renderScale, renderScale);
}


void Screen::pixel(float x, float y) {
	SDL_FPoint* point = new SDL_FPoint();
	point->x = x;
	point->y = y;
	points.push_back(*point);
}


void Screen::show() {
	//SDL_SetRenderDrawColor(renderer, 29, 39, 49, 255);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//SDL_SetRenderDrawColor(renderer, 217, 179, 16, 255);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (auto& point : points) {
		SDL_RenderDrawPointF(renderer, point.x, point.y);
	}

	SDL_RenderPresent(renderer);
}


void Screen::clear() {
	points.clear();
}

void Screen::input() {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
	}
}
