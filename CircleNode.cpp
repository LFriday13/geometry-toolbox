/*
 * CircleNode.cpp
 *
 */

#include <cmath>
#include <limits>
#include "CircleNode.h"

CircleNode::CircleNode() {}

CircleNode::CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2) : GeoNode(2) {
	switch(type) {
		case POINT_POINT_CENTER_THROUGH: definition = &CircleNode::point_point_center_through; break;
	}

	parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
	(this->*definition)();
}

CircleNode::CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3) : GeoNode(3) {
	switch(type) {
		case POINT_POINT_POINT_THROUGH: definition = &CircleNode::point_point_point_through; break;
		case POINT_POINT_POINT_CENTER_RADIUS: definition = &CircleNode::point_point_point_center_radius; break;
	}

	parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
	parents[2] = geo3;
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
	double p1[2], p2[2], p3[2];
	parents[0]->access(p1);
	parents[1]->access(p2);
	parents[2]->access(p3);
	
	center_x = ((p1[0]*p1[0] - p3[0]*p3[0]) * (p1[0] - p2[0]) 
		+ (p1[1]*p1[1]-p3[1]*p3[1]) * (p1[0] - p2[0]) 
		+ (p2[0]*p2[0]-p1[0]*p1[0]) * (p1[0]-p3[0]) 
        + (p2[1]*p2[1]-p1[1]*p1[1]) * (p1[0]-p3[0]));
		
    center_x /=  2 * ((p3[1]-p1[1]) * (p1[0] - p2[0]) - (p2[1]-p1[1]) * (p1[0]-p3[0]));
	
    center_y = ((p1[0]*p1[0] - p3[0]*p3[0]) * (p1[1]-p2[1]) 
		+ (p1[1]*p1[1]-p3[1]*p3[1]) * (p1[1]-p2[1]) 
		+ (p2[0]*p2[0]-p1[0]*p1[0]) * (p1[1]-p3[1]) 
		+ (p2[1]*p2[1]-p1[1]*p1[1]) * (p1[1]-p3[1]));
		
	center_y /= 2 * ((p3[0]-p1[0]) * (p1[1]-p2[1]) - (p2[0]-p1[0]) * (p1[1]-p3[1])); 
	
	radius = sqrt((p1[0]-center_x)*(p1[0]-center_x) + (p1[1]-center_y)*(p1[1]-center_y));
}

void CircleNode::point_point_center_through(){
	double p1[2], p2[2];
	parents[0]->access(p1);
	parents[1]->access(p2);
	
	center_x = p1[0];
	center_y = p1[1];
	
	radius = sqrt((p2[0] - center_x)*(p2[0] - center_x) + (p2[0] - center_x)*(p2[0] - center_x));
}
	
void CircleNode::point_point_point_center_radius(){
	double p1[2], p2[2], p3[2];
	parents[0]->access(p1);
	parents[1]->access(p2);
	parents[2]->access(p3);
	
	center_x = p1[0];
	center_y = p1[1];
	
	radius = sqrt((p3[0] - p2[0])*(p3[0] - p2[0]) + (p3[1] - p2[1])*(p3[1] - p3[1]));
}