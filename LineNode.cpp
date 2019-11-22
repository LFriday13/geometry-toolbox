/*
 * LineNode.cpp
 *
 */

#include <math.h>
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
	//TODO
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
	//TODO
}

void LineNode::point_line_parallel_line_through() {
	//TODO
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
