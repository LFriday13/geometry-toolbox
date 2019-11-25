/*
 * CircleNode.cpp
 *
 */

#include <cmath>
#include <limits>
#include "CircleNode.h"

CircleNode::CircleNode() {}

CircleNode::CircleNode(CircleType type, double center_x, double center_y, double radius) : center_x(center_x), center_y(center_y), definition(&CircleNode::independent) {}

CircleNode::CircleNode(CircleType type, GeoNode* geo1, double radius) : GeoNode(1) {
	switch(type) {
		case POINT_POINT_POINT_THROUGH: definition = &CircleNode::point_center_radius; break;
	}

	parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	(this->*definition)();
}

CircleNode::CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2) : GeoNode(2) {
	switch(type) {
		case POINT_POINT_POINT_THROUGH: definition = &CircleNode::point_point_point_through; break;
		case POINT_POINT_CENTER_THROUGH: definition = &CircleNode::point_point_center_through; break;
	}

	parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
	(this->*definition)();
}

CircleNode::~CircleNode() {}

void CircleNode::print() const {
	cout << "----------------------------------------\n";
	cout << "Identifier: " << this->get_label() << endl;
	cout << "Data: " << center_x << '\t' << center_y << '\t' << radius << endl;
	cout << "Parents:";
	for(int i = 0; i < num_parents;++i)
		cout << " " << parents[i]->get_label();
	cout << endl;
}

void CircleNode::display() const {
	//TODO
}

void CircleNode::access(double data[]) const {
	data[0] = center_x;
	data[1] = center_y;
	data[2] = radius;
}

void CircleNode::mutate(double data[]) {
	center_x = data[0];
	center_y = data[1];
	radius = data[2];
	(this->*definition)();
}

void CircleNode::update() {
	(this->*definition)();
}

void CircleNode::point_point_point_through() {
	//TODO
}

void CircleNode::point_point_center_through(){
	//TODO
}
	
void CircleNode::point_center_radius(){
	//TODO
}
	
void CircleNode::independent() {}