/*
 * PointNode.cpp
 *
 */

#include <math.h>
#include "PointNode.h"

PointNode::PointNode() {}

PointNode::PointNode(PointType type, double x, double y) : x(x), y(y), definition(independent) {}

PointNode::PointNode(PointType type, GeoNode* geo1, double x, double y) : num_parents(1) {

	switch(type) {
		case ON_LINE: definition = on_line; break;
		case ON_CIRCLE:	definition = on_circle; break;
	}

	parents = new GeoNode*[num_parents];
	parents[0] = geo1;
	this->x = x;
	this->y = y;
	definition();
}

PointNode::PointNode(PointType type, GeoNode* geo1, GeoNode* geo2) : num_parents(2) {

	switch(type) {
		case POINT_POINT_MIDPOINT: definition = point_point_midpoint; break;
		case LINE_LINE_INTERSECTION: definition = line_line_intersection; break;
		case LINE_CIRCLE_HIGHER_INTERSECTION: definition = line_circle_higher_intersection; break;
		case LINE_CIRCLE_LOWER_INTERSECTION: definition = line_circle_lower_intersection; break;
		case CIRCLE_CIRCLE_HIGHER_INTERSECTION: definition = circle_circle_higher_intersection; break;
		case CIRCLE_CIRCLE_LOWER_INTERSECTION: definition = circle_circle_lower_intersection; break;
	}

	parents = new GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
	definition();
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
	definition();
}

virtual void PointNode::update() {
	definition();
}

void PointNode::independent() {}

void PointNode::on_line() {
	double line[3];
  parents[0]->access(line);
  double t = (line[0] * x + line[1] * y - line[2])/(line[0] * line[0] + line[1] * line[1]);
  x -= line[0] * t;
  y -= line[1] * t;
}

void PointNode::on_circle() {
	double circle[3];
  parents[0]->access(circle);
  double current_radius = sqrt((x - circle[0]) * (x - circle[0]) + (y - circle[1]) * (y - circle[1]));
  x = circle[0] + (x - circle[0]) * radius / current_radius;
  y = circle[1] + (y - circle[1]) * radius / current_radius;
}

void PointNode::point_point_midpoint() {
	double p1[2], p2[2];
	parents[0]->access(p1);
	parents[1]->access(p2);

	x = (p1[0]+p2[0])/2;
	y = (p1[1]+p2[1])/2;
}

void PointNode::line_line_intersection() {
	  double delta, delta_x, delta_y;
	  double line1[3], line2[3];
    parents[0]->access(line1);
    parents[1]->access(line2);
	  delta = line1[0] * line2[1] - line1[1] * line2[0];
	  delta_x = line1[3] * line2[1] - line1[1] * line2[3];
	  delta_y = line1[0] * line2[3] - line1[3] * line2[0];
	  x = delta_x / delta;
	  y = delta_y / delta;
}

void PointNode::line_circle_higher_intersection() {
	//TODO
}

void PointNode::line_circle_lower_intersection() {
	//TODO
}

void PointNode::circle_circle_higher_intersection() {
	//TODO
}

void PointNode::circle_circle_lower_intersection() {
	//TODO
}
