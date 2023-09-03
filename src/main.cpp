#include "screen.h"
#include <numeric>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

struct point {
	long double x, y, z;
};

struct edge {
	int a, b;
};

std::vector<point> points{
	{100, 100, 100},
	{200, 100, 100},
	{200, 200, 100},
	{100, 200, 100},

	{100, 100, 200},
	{200, 100, 200},
	{200, 200, 200},
	{100, 200, 200},

};

std::vector<edge> edges{
	{0, 4},
	{1, 5},
	{2, 6},
	{3, 7},

	{0, 1},
	{1, 2},
	{2, 3},
	{3, 0},

	{4, 5},
	{5, 6},
	{6, 7},
	{7, 4}
};


std::vector<point> rotate(std::vector<point> points, point center, float rX = 0, float rY = 0, float rZ = 0) {

	for (auto& p : points) {
		p.x -= center.x;
		p.y -= center.y;
		p.z -= center.z;

		float theta = rX;
		float y1 = p.y;
		p.y = (cos(theta) * p.y) + (-sin(theta) * p.z);
		p.z = (sin(theta) * y1) + (cos(theta) * p.z);

		theta = rY;
		float x1 = p.x;
		p.x = (cos(theta) * p.x) + (sin(theta) * p.z);
		p.z = (-sin(theta) * x1) + (cos(theta) * p.z);

		theta = rZ;
		float x2 = p.x;
		p.x = (cos(theta) * p.x) + (-sin(theta) * p.y);
		p.y = (sin(theta) * x2) + (cos(theta) * p.y);

		p.x += center.x;
		p.y += center.y;
		p.z += center.z;

	}
	return points;


}



void add_pixels_in_line(Screen& screen, float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float length = sqrt(pow(dx, 2) + pow(dy, 2));
	float angle = atan2(dy, dx);

	for (float i = 0; i < length; i++) {
		screen.pixel(
						x1 + cos(angle) * i,
						y1 + sin(angle) * i
					);
	}

}

point find_center(std::vector<point> points) {
	point center{ 0, 0, 0 };
	for (auto& p : points) {
		center.x += p.x;
		center.y += p.y;
		center.z += p.z;

	}
	center.x /= points.size();
	center.y /= points.size();
	center.z /= points.size();
	return center;

}

int main(int argc, char** argv) {

	Screen screen;
	//std::string message = "HI";
	//for (auto& i : message) {
	//	//invoke frame classe's method to add a letter to the frame
	//}



	point center = find_center(points);


	float xRotationFactor = 0.03;
	float yRotationFactor = 0.02;
	float zRotationFactor = 0.01;
	float xRotationValue = 0;
	float yRotationValue = 0;
	float zRotationValue = 0;
	while (true) {
		
		std::vector<point> newPoints = rotate(points, center, xRotationValue, yRotationValue, zRotationValue);
		for (auto& p : newPoints) {
			screen.pixel(p.x, p.y);
		}
		for (auto& edge : edges) {
			add_pixels_in_line(screen, newPoints[edge.a].x, newPoints[edge.a].y, newPoints[edge.b].x, newPoints[edge.b].y);
		}

		screen.show();
		screen.clear();
		screen.input();
		SDL_Delay(10);
		xRotationValue += xRotationFactor;
		yRotationValue += yRotationFactor;
		zRotationValue += zRotationFactor;
		
	}
	return 0;
}