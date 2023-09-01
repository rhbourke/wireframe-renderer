#include "screen.h"
#include <numeric>
#include <math.h>
using namespace std;

struct vec3 {
	float x, y, z;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1) {

	float rad = x;
	point.y = cos(rad) * point.y - sin(rad) * point.z;
	point.z = sin(rad)* point.y + cos(rad) * point.z;

	rad = y;
	point.x = cos(rad) * point.x + sin(rad) * point.z;
	point.z = -sin(rad) * point.x + cos(rad) * point.z;

	rad = z;
	point.x = cos(rad) * point.x - sin(rad) * point.y;
	point.y = sin(rad) * point.x + cos(rad) * point.y;

}

struct connection {
	int a, b;
};


void line(Screen& screen, float x1, float y1, float x2, float y2) {
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

int main(int argc, char** argv){

	Screen screen;

	vector<vec3> points{
		{100, 100, 100},
		{200, 100, 100},
		{200, 200, 100},
		{100, 200, 100},

		{100, 100, 200},
		{200, 100, 200},
		{200, 200, 200},
		{100, 200, 200},

	};

	vector<connection> edges{
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

	//Finds average of all the points to get the shape's center
	vec3 centeroid{ 0, 0, 0 };
	for (auto& p : points) {
		centeroid.x += p.x;
		centeroid.y += p.y;
		centeroid.z += p.z;

	}
	centeroid.x /= points.size();
	centeroid.y /= points.size();
	centeroid.z /= points.size();


	while (true) {
		for (auto& p : points) {
			p.x -= centeroid.x;
			p.y -= centeroid.y;
			p.z -= centeroid.z;
			rotate(p, 0.002, 0.001, 0.004);
			p.x += centeroid.x;
			p.y += centeroid.y;
			p.z += centeroid.z;
			screen.pixel(p.x, p.y);
		}
		for (auto& edge : edges) {
			line(screen, points[edge.a].x, points[edge.a].y, points[edge.b].x, points[edge.b].y);
		}
		screen.show();
		screen.clear();
		screen.input();
		SDL_Delay(3);
	}
	return 0;
}