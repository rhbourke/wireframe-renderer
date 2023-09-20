#include "screen.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "frame.h"
#include "SDL2/include/SDL.h"
#include "letters.h"

// Input a text string to prompt the user with and a reference to the value you want to update
void get_user_selection(std::string prompt, std::string &option) {
	try {
		std::cout << prompt;
		std::string choice = "";
		std::getline(std::cin, choice);
		option = choice;
	}
	catch(...) {
		std::cout << "\nInvalid input! Try again!\n";
		get_user_selection(prompt, option);
	}
}

void get_user_selection(std::string prompt, int &option) {
	try {

		std::cout << prompt;
		std::string choice = "";
		std::getline(std::cin, choice);
		option = stoi(choice);
	}
	catch (...) {
		std::cout << "\nInvalid input! Try again!\n";
		get_user_selection(prompt, option);
	}
}

void add_pixels_in_line(Screen& screen, float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float length = std::sqrt(std::pow(dx, 2.0f) + std::pow(dy, 2.0f));
	float angle = std::atan2(dy, dx);

	for (int i = 0; i < length; i++) {
		screen.pixel(x1 + std::cos(angle) * i, y1 + std::sin(angle) * i);
	} 

}

// returns bigger values when xR, yR, zR are farther from an angle of 0, used to make text move faster when it is in unreadable rotational positions
float calculate_rotation_scale(float xR, float yR, float zR) {
	xR = std::fmod(xR, (3.14 * 2));
	yR = std::fmod(yR, (3.14 * 2));
	zR = std::fmod(zR, (3.14 * 2));
	float xFact = std::min(std::max(abs(3.14 - xR), 1.0), 2.0);
	float yFact = std::min(std::max(abs(3.14 - yR), 1.0), 2.0);
	float zFact = std::min(std::max(abs(3.14 - zR), 1.0), 2.0);
	float scale = .01/(xFact * yFact * zFact);
	return scale;
}

int main(int argc, char** argv) {

	int width = 1920;
	int height = 1080;
	int renderScalePercent = 100;
	float delay = 100;
	std::string message;
	std::string skipAdvancedOptions;
	int letterDepth = 30;
	float rotScale = 1;

	// Amount to rotate by each time we draw (hundreths of radians)
	int xRotationFactor = 4;
	int yRotationFactor = 2;
	int zRotationFactor = 2;

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

	get_user_selection("Enter message to display: ", message);
	if (message.size() >= 12) {
		std::cout << "\nYour message is a little longer than intended for the program. You might want to configure a render size percentage less than 100, or shorten your message.";
	}
	for (auto& c : message) c = std::toupper(c);
	
	get_user_selection("\nSkip advanced options? (Y/N): ", skipAdvancedOptions);
	for (auto& c : skipAdvancedOptions) c = std::toupper(c);

	if (skipAdvancedOptions != "Y") {
		get_user_selection("\nEnter screen width (pixels): ", width);
		get_user_selection("\nEnter screen height (pixels): ", height);
		get_user_selection("\nEnter the scale percentage (default is 100): ", renderScalePercent);
		std::cout << "\nNow, enter the rotation factor per frame in hundreths of radians. Default values are " + std::to_string(xRotationFactor) + ", " + std::to_string(yRotationFactor) + ", " + std::to_string(zRotationFactor) + " for X, Y, and Z respectively.";
		get_user_selection("\nX: ", xRotationFactor);
		get_user_selection("\nY: ", yRotationFactor);
		get_user_selection("\nZ: ", zRotationFactor);
		std::cout << "\nNow, enter the RGB values (from 0-255) for the color of the background: ";
		get_user_selection("\nR: ", backgroundColor.r);
		get_user_selection("\nG: ", backgroundColor.g);
		get_user_selection("\nB: ", backgroundColor.b);
		std::cout << "\nNow, enter the RGB values (from 0-255) for the color of the wireframe: ";
		get_user_selection("\nR: ", drawColor.r);
		get_user_selection("\nG: ", drawColor.g);
		get_user_selection("\nB: ", drawColor.b);
		std::cout << "\nEnter a value to represent the depth of the letters. Smaller => thinner, larger => wider. Default is 20.";
		get_user_selection("\nLetter depth: ", letterDepth);
		std::cout << "\nConfiguration complete";

	}
	std::cout << "\n\nRendering wireframe...";

	Screen screen(width, height, renderScalePercent, backgroundColor, drawColor);

	Frame wireframe;
	wireframe.letterDepth = letterDepth;
	wireframe.add_text(width, height, renderScalePercent, message);

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

		rotScale = calculate_rotation_scale(xRotationValue, yRotationValue, zRotationValue);
		xRotationValue += xRotationFactor * rotScale;
		yRotationValue += yRotationFactor * rotScale;
		zRotationValue += zRotationFactor * rotScale;

		SDL_Delay(2);
		
	}
	return 0;
}