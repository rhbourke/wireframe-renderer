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
	for (auto& piece : newPieces) { //convert pieces into vector of edges
		for (int i = piece.first; i < piece.last; i++) {
			edge newEdge = { i, i + 1 };
			newEdges.push_back(newEdge);
		}
		edge newEdge = { piece.last, piece.first };
		newEdges.push_back(newEdge);
	}
	for (auto e : newEdges) { //add regular edges
		e.a += points.size();
		e.b += points.size();
		edges.push_back(e);
	}
	for (auto e : newEdges) { //add edges on back part of character
		e.a += points.size() + newEdges.size();
		e.b += points.size() + newEdges.size();
		edges.push_back(e);
	}
	for (int i = 0; i < newEdges.size(); i++) { //add edges to connect front and back part of character
		edge depthEdge = { i, i + newEdges.size() };
		depthEdge.a += points.size();
		depthEdge.b += points.size();
		edges.push_back(depthEdge);
	}

}

void Frame::add_text(std::string text) {
	for (int i = 0; i < text.size(); i++) {
		for (auto& letter : alphabet) {
			if (text[i] == letter.name) {
				std::vector<point> newPoints = letter.points;
				for (auto& p : letter.points) {
					point depthPoint = { p.x, p.y, p.z + 20 };
					newPoints.push_back(depthPoint);
				}
				add_edges(letter.pieces);
				for (auto& p : newPoints) {
					p.x += 115 * i;
				}
				add_points(newPoints);
				continue;
			}

		}
	}
}

void Frame::update_center(int width, int height, int renderScalePercent) {
	float renderScale = renderScalePercent * 0.01;
	center = { 0, 0, 0 };
	for (auto& p : points) {
		center.x += p.x;
		center.y += p.y;
		center.z += p.z;
	}
	center.x /= points.size();
	center.y /= points.size();
	center.z /= points.size();
	for (auto& p : points) {
		p.x += ((width / 2) - center.x*renderScale) * (1/renderScale);
		p.y += ((height / 2) - center.y*renderScale) * (1/renderScale);
	}
	center.x = width / (2*renderScale);
	center.y = height / (2*renderScale);
}

std::vector<edge> Frame::get_edges() {
	return edges;
}

std::vector<point> Frame::generate_rotated_frame(float rX, float rY, float rZ) {

	std::vector<point> newFrame = points;

	for (auto& p : newFrame) {
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