#ifndef FRAME_H
#define FRAME_H


#include <vector>
#include "letters.h"
#include <string>

struct point {
	int x, y, z;
};
struct edge {
	int a, b;
};

class Frame {
	
	

	std::vector<point> points{};

	std::vector<edge> edges{};

	point center = point{ 0, 0, 0 };

	void add_points(std::vector<point> newPoints);

	void add_edges(std::vector<piece> newPieces);

public:

	int letterDepth;

	// Takes an input string and breaks it down into points and edges, adding them to the wireframe
	void add_text(std::string text);

	// Shifts the wireframe to the center of the screen and updates the center of rotation
	void update_center(int width, int height, int renderScalePercent);

	std::vector<edge> get_edges();

	// Returns a copy of the wireframe after rotating it in all 3 dimensions by the given amount
	std::vector<point> generate_rotated_frame(float rX = 0, float rY = 0, float rZ = 0);

};

#endif