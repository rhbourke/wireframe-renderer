#include "frame.h"
#include <cmath>
#include <vector>

void Frame::add_points(std::vector<point> newPoints) {
	for (auto& p : newPoints) {
		points.push_back(p);
	}
}
void Frame::add_edges(std::vector<piece> newPieces) {
	std::vector<edge> newEdges;
	for (auto& piece : newPieces) { // convert pieces into vector of edges
		for (int i = piece.first; i < piece.last; i++) {
			edge newEdge = { i, i + 1 };
			newEdges.push_back(newEdge);
		}
		edge newEdge = { piece.last, piece.first };
		newEdges.push_back(newEdge);
	}
	for (auto e : newEdges) { // add edges on front part of character
		e.a += points.size();
		e.b += points.size();
		edges.push_back(e);
	}
	for (auto e : newEdges) { // add edges on back part of character
		e.a += points.size() + newEdges.size();
		e.b += points.size() + newEdges.size();
		edges.push_back(e);
	}
	for (int i = 0; i < newEdges.size(); i++) { // add edges to connect front and back parts of character
		edge depthEdge = { i, i + newEdges.size() };
		depthEdge.a += points.size();
		depthEdge.b += points.size();
		edges.push_back(depthEdge);
	}

}

std::vector<edge> Frame::get_edges() {
	return edges;
}

void Frame::update_center(int width, int height, int renderScalePercent, int messageLength) {

	float renderScale = renderScalePercent * 0.01;

	// Calculating the center of the figure we want to render:
	center = { 0, 0, 0 };
	center.x = ((letterWidth * messageLength) + (letterSpacing * (messageLength - 1))) / 2;
	center.y = letterHeight / 2;
	center.z = letterDepth / 2;

	// Update all of the points so they appear in the center of the screen
	for (auto& p : points) {
		p.x += ((width / 2) - center.x * renderScale) * (1 / renderScale);
		p.y += ((height / 2) - center.y * renderScale) * (1 / renderScale);
	}

	// We just moved all of the points so that the text is in the center of the screen. Now update the actual center so it is accurate again.
	center.x = width / (2 * renderScale);
	center.y = height / (2 * renderScale);
}

void Frame::add_text(int width, int height, int renderScalePercent, std::string text) {

	for (int i = 0; i < text.size(); i++) { //Iterate through the characters in 'text' param
		for (auto& letter : alphabet) { // Look for matches in alphabet vector
			if (text[i] == letter.name) {
				std::vector<point> newPoints;
				for (auto& p : letter.points) { // Convert all of the point2Ds in the letter to 3D points with z=0
					point frontPoint = { p.x, p.y, 0 };
					newPoints.push_back(frontPoint);
				}
				for (auto& p : letter.points) { // Also add those same points but with some depth added
					point depthPoint = { p.x, p.y, letterDepth};
					newPoints.push_back(depthPoint);
				}
				add_edges(letter.pieces);
				for (auto& p : newPoints) { // Shift each point according to its position in the message
					p.x += (letterWidth + letterSpacing) * i;
				}
				add_points(newPoints);
				continue;
			}

		}
	}
	update_center(width, height, renderScalePercent, text.size());
}


// Rotate the frame's collection of points in 3 dimensions, parameters in radians
std::vector<point> Frame::generate_rotated_frame(float rX, float rY, float rZ) {

	std::vector<point> newFrame = points;

	for (auto& p : newFrame) {

		// It is mathematically easier to rotate around the origin, so we will shift everything to be centered there then shift back after
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
	return newFrame;


}