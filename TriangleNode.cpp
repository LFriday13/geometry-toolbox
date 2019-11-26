/*
 * TriangleNode.cpp
 *
 */
#include "TriangleNode.h"

TriangleNode::TriangleNode() {}

TriangleNode::TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3): GeoNode(3) {
  switch(type) {
		case POINT_POINT_POINT_VERTICES: definition = &TriangleNode::point_point_point_vertices; break;
		case LINE_LINE_LINE_INTERSECTIONS: definition = &TriangleNode::line_line_line_intersections; break;
	}
  parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
	parents[1] = geo2;
  parents[2] = geo3;
	(this->*definition)();
}

void TriangleNode::print() const {

}

void TriangleNode::display() const {

}

void TriangleNode::access(double data[]) const {
  data[0] = side_a;
  data[1] = side_b;
  data[2] = side_c;
}

void TriangleNode::mutate(double data[]) {

}

void TriangleNode::update() {
  (this->*definition)();
}

TriangleNode::~TriangleNode() {}

void TriangleNode::point_point_point_vertices() {

}

void TriangleNode::line_line_line_intersections() {
  
}
