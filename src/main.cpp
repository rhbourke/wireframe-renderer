#include "screen.h"
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "frame.h"
#include "SDL2/include/SDL.h"
#include "letters.h"

void get_option_choice(std::string prompt, std::string &option) {
	std::cout << prompt;
	std::string choice = "";
	std::getline(std::cin, choice);
	option = choice;
}

void get_option_choice(std::string prompt, int &option) {
	std::cout << prompt;
	std::string choice = "";
	std::getline(std::cin, choice);
	option = stoi(choice);
}

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
	float scale = xFact * yFact * zFact;
	return scale;
}

int main(int argc, char** argv) {

	int width = 1920;
	int height = 1080;
	int renderScalePercent = 100;
	float delay = 100;
	std::string message;
	std::string skipAdvancedOptions;
	int letterDepth = 20;

	// Amount to rotate by each time we draw (hundreths of radians)
	int xRotationFactor = 2;
	int yRotationFactor = 1;
	int zRotationFactor = 1;

	// Initial rotation amounts
	float xRotationValue = 0;
	float yRotationValue = 0;
	float zRotationValue = 0;

	rgb backgroundColor = {
		0, 0, 0
	};

	rgb drawColor = {
		255, 255, 255
	};

	get_option_choice("Enter message to display: ", message);
	if (message.size() >= 12) {
		std::cout << "\nYour message is a little longer than intended for the program. You might want to configure a render size percentage less than 100, or shorten your message.";
	}
	for (auto& c : message) c = std::toupper(c);
	
	get_option_choice("\nSkip advanced options? (Y/N): ", skipAdvancedOptions);
	for (auto& c : skipAdvancedOptions) c = std::toupper(c);

	if (skipAdvancedOptions != "Y") {
		get_option_choice("\nEnter screen width (pixels): ", width);
		get_option_choice("\nEnter screen height (pixels): ", height);
		get_option_choice("\nEnter the scale percentage (default is 100): ", renderScalePercent);
		std::cout << "\nNow, enter the rotation factor per frame in hundreths of radians. Default values are " + std::to_string(xRotationFactor) + ", " + std::to_string(yRotationFactor) + ", " + std::to_string(zRotationFactor) + " for X, Y, and Z respectively.";
		get_option_choice("\nX: ", xRotationFactor);
		get_option_choice("\nY: ", yRotationFactor);
		get_option_choice("\nZ: ", zRotationFactor);
		std::cout << "\nNow, enter the RGB values (from 0-255) for the color of the background: ";
		get_option_choice("\nR: ", backgroundColor.r);
		get_option_choice("\nG: ", backgroundColor.g);
		get_option_choice("\nB: ", backgroundColor.b);
		std::cout << "\nNow, enter the RGB values (from 0-255) for the color of the wireframe: ";
		get_option_choice("\nR: ", drawColor.r);
		get_option_choice("\nG: ", drawColor.g);
		get_option_choice("\nB: ", drawColor.b);
		std::cout << "\nEnter a value to represent the depth of the letters. Smaller => thinner, larger => wider. Default is 20.";
		get_option_choice("\nLetter depth: ", letterDepth);
		std::cout << "\nConfiguration complete";

	}
	std::cout << "\n\nRendering wireframe...";

	Screen screen(width, height, renderScalePercent, backgroundColor, drawColor);
	Frame wireframe;
	wireframe.letterDepth = letterDepth;
	
	wireframe.add_text(message);
	wireframe.update_center(width, height, renderScalePercent);

	
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
		xRotationValue += xRotationFactor * 0.01;
		yRotationValue += yRotationFactor * 0.01;
		zRotationValue += zRotationFactor * 0.01;
		
	}
	return 0;
}