/*
 * PointNode.cpp
 *
 */

#include "PointNode.h"

PointNode::PointNode() {}

PointNode::PointNode(PointType type, double x, double y) : x(x), y(y), update_this(independent) {}

PointNode::PointNode(PointType type, GeoNode* geo1, double x, double y) {
	//TODO
}

PointNode::PointNode(PointType type, GeoNode* geo1, GeoNode* geo2) {
	//TODO
}

virtual PointNode::~PointNode() {}

virtual void PointNode::print() const {
	//TODO
}

virtual void PointNode::display() const {
	//TODO
}

virtual void PointNode::access(double data[]) const {
	data[0] = x;
	data[1] = y;
}

virtual void PointNode::mutate(double data[]) {
	x = data[0];
	y = data[1];
	update_this();
}

virtual void PointNode::update() {
	update_this();
}

void PointNode::independent() {}

void PointNode::on_line() {
	//TODO
	//Adjust x and y to be on the line which is parents[0]
}

void PointNode::on_circle() {
	//TODO
	//Adjust x and y to be on the circle which is parents[0]
}

void PointNode::point_point_midpoint() {
	//TODO
}

void PointNode::line_line_intersection() {
	//TODO
}

void PointNode::line_circle_intersection() {
	//TODO
}

void PointNode::circle_circle_higher_intersection() {
	//TODO
}

void PointNode::circle_circle_lower_intersection() {
	//TODO
}

/*
function name: line_line_intersection
property: mutator
parameters:
prm[0]: line 1 x-coefficient
prm[1]: line 1 y-coefficient
prm[2]: line 1 c-coefficient
prm[3]: line 2 x-coefficient
prm[4]: line 2 y-coefficient
prm[5]: line 2 c-coefficient
implementation sketch: Cramer's rule

void line_line_intersection(double prm[]) {
  double delta, delta_x, delta_y;
  double x_coeff[2] = {prm[0], prm[3]};
  double y_coeff[2] = {prm[1], prm[4]};
  double c_coeff[2] = {prm[2], prm[5]};
  delta = x_coeff[0] * y_coeff[1] - x_coeff[1] * y_coeff[0];
  delta_x = c_coeff[0] * y_coeff[1] - c_coeff[1] * y_coeff[0];
  delta_y = x_coeff[0] * c_coeff[1] - x_coeff[1] * c_coeff[0];
  x = delta_x / delta;
  y = delta_y / delta;
}
*/
