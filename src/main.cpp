#include "screen.h"
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "frame.h"
#include <SDL.h>
#include "letters.h"

void add_pixels_in_line(Screen& screen, float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float length = std::sqrt(std::pow(dx, 2.0f) + std::pow(dy, 2.0f));
	float angle = std::atan2(dy, dx);

	for (int i = 0; i < length; i++) {
		screen.pixel(
						x1 + std::cos(angle) * i,
						y1 + std::sin(angle) * i
					);
	} 

}

float delay_scale(float xR, float yR, float zR) {
	xR = xR / (3.14*2);
	yR = yR / (3.14*2);
	zR = zR / (3.14*2);
	float xFact = abs(.5-(xR - (long)xR));
	float yFact = abs(.5-(yR - (long)yR));
	float zFact = abs(.5-(zR - (long)zR));
	float scale = xFact + yFact + zFact;
	return scale;
}

int main(int argc, char** argv) {

	int width = 1920;
	int height = 1080;
	Screen screen(width, height);
	Frame wireframe;

	std::string message = "BAAABAA";
	wireframe.add_text(message);

	wireframe.update_center(width, height);

	//Amount to rotate by each time we draw (radians)
	float xRotationFactor = 0.03f; 
	float yRotationFactor = 0.03f;
	float zRotationFactor = 0.02f;
	/*float xRotationFactor = 0.00f;
	float yRotationFactor = 0.00f;
	float zRotationFactor = 0.00f;*/

	//Initial rotation amount
	float xRotationValue = 0; 
	float yRotationValue = 0;
	float zRotationValue = 0;

	float delay = 7;
	while (true) {
		
		std::vector<point> newPoints = wireframe.generate_rotated_frame(xRotationValue, yRotationValue, zRotationValue);
		for (auto& p : newPoints) {
			screen.pixel(p.x, p.y);
		}
		for (auto& edge : wireframe.get_edges()) {
			add_pixels_in_line(screen, newPoints[edge.a].x, newPoints[edge.a].y, newPoints[edge.b].x, newPoints[edge.b].y);
		}

		screen.show();
		screen.clear();
		screen.input();
		SDL_Delay(delay * delay_scale(xRotationValue, yRotationValue, zRotationValue));
		xRotationValue += xRotationFactor;
		yRotationValue += yRotationFactor;
		zRotationValue += zRotationFactor;
		
	}
	return 0;
}