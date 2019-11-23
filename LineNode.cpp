/*
 * LineNode.cpp
 *
 */

#include <cmath>
#include <limits>
#include "LineNode.h"

LineNode::LineNode() {}

LineNode::LineNode(LineType type, GeoNode* geo1, GeoNode* geo2)  : GeoNode(2) {

	switch(type) {
		case POINT_POINT_LINE_THROUGH: definition = point_point_line_through; break;
		case POINT_LINE_PARALLEL_LINE_THROUGH: definition = point_line_parallel_line_through; break;
		case POINT_POINT_PERPENDICULAR_BISECTOR: definition = point_point_perpendicular_bisector; break;
		case POINT_CIRCLE_FIRST_TANGENT: definition = point_circle_first_tangent; break;
		case POINT_CIRCLE_SECOND_TANGENT: definition = point_circle_second_tangent; break;
	}

	parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
	(this->*definition)();
}

LineNode::~LineNode() {}

void LineNode::print() const {
	cout << "----------------------------------------\n";
	cout << "Identifiers: " << this->get_label() << endl;
	cout << "Data: " << x_coeff << '\t' << y_coeff << '\t' << c_coeff << endl;
	cout << "Parents:";
	for(int i = 0; i < num_parents;++i)
		cout << parents[i]->get_label();
	cout << endl;
}

void LineNode::display() const {
	//TODO
}

void LineNode::access(double data[]) const {
	data[0] = x_coeff;
	data[1] = y_coeff;
	data[2] = c_coeff;
}

void LineNode::mutate(double data[]) {
	x_coeff = data[0];
	y_coeff = data[1];
	c_coeff = data[2];
	(this->*definition)();
}

void LineNode::update() {
	(this->*definition)();
}

void LineNode::point_point_line_through() {
	double p1[2], p2[2];
	parents[0]->access(p1);
	parents[1]->access(p2);
	
	x_coeff = p1[1] - p2[1];
	y_coeff = p2[0] - p1[0];
	
	if(x_coeff < std::numeric_limits<double>::epsilon() && x_coeff > -std::numeric_limits<double>::epsilon()) {
		if(y_coeff < std::numeric_limits<double>::epsilon() && y_coeff > -std::numeric_limits<double>::epsilon())
			well_defined = false;
	} else { 
		c_coeff = (-y_coeff)*p1[1] + (-x_coeff)*p1[0];
	}
}

void LineNode::point_line_parallel_line_through() {
	double point[2], line[3];
	parents[0]->access(point);
	parents[1]->access(line);
	
	x_coeff = line[0];
	y_coeff = line[1];
	
	c_coeff = (-y_coeff)*point[1] + (-x_coeff)*point[0];
}

void LineNode::point_point_perpendicular_bisector() {
	//TODO
}

void LineNode::point_circle_first_tangent() {
	//TODO
	//If the point is inside the circle, set well_defined as false
	//Otherwise, calculate the tangent normally
}

void LineNode::point_circle_second_tangent() {
	//TODO
	//If the point is inside or on the circle, set well_defined as false
	//Otherwise, calculate the tangent normally
}
