/*
 * TriangleNode.cpp
 *
 */
#include <math.h>
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
  cout << "----------------------------------------\n";
	cout << "Identifier: " << this->get_label() << endl;
	cout << "Data: " << side_a << '\t' << side_b << '\t' << side_c << endl;
	cout << "Parents:";
	for(int i = 0; i < num_parents;++i)
		cout << " " << parents[i]->get_label();
	cout << endl;
}

void TriangleNode::display() const {

}

void TriangleNode::access(double data[]) const {
  data[0] = side_a;
  data[1] = side_b;
  data[2] = side_c;
}

void TriangleNode::mutate(double data[]) {
  side_a = data[0];
  side_b = data[1];
  side_c = data[2];
  (this->*definition)();
}

void TriangleNode::update() {
  (this->*definition)();
}

TriangleNode::~TriangleNode() {}

void TriangleNode::point_point_point_vertices() {
  double point1[2], point2[2], point3[2];
  parents[0]->access(point1);
  parents[1]->access(point2);
  parents[2]->access(point3);
  side_a = sqrt((point2[0] - point3[0]) * (point2[0] - point3[0]) + (point2[1] - point3[1]) * (point2[1] - point3[1]));
  side_b = sqrt((point3[0] - point1[0]) * (point3[0] - point1[0]) + (point3[1] - point1[1]) * (point3[1] - point1[1]));
  side_c = sqrt((point1[0] - point2[0]) * (point1[0] - point2[0]) + (point1[1] - point2[1]) * (point1[1] - point2[1]));
  if(side_a > 1e-8 && side_b > 1e-8 && side_c > 1e-8) well_defined = true;
  else well_defined = false;
}

void TriangleNode::get_intersection_helper(double line1[], double line2[], double point[]) {
    double delta = line1[0] * line2[1] - line1[1] * line2[0];
    if(delta < 1e-8 && delta > -1e-8)
        well_defined = false;
    else{
        double delta_x = line1[2] * line2[1] - line1[1] * line2[2];
        double delta_y = line1[0] * line2[2] - line1[2] * line2[0];
        point[0] = -delta_x / delta;
        point[1] = -delta_y / delta;
    }
}

void TriangleNode::line_line_line_intersections() {
  double line1[3], line2[3], line3[3];
  parents[0]->access(line1);
  parents[1]->access(line2);
  parents[2]->access(line3);
  double point1[2], point2[2], point3[2];
  well_defined = true;
  get_intersection_helper(line2, line3, point1);
  get_intersection_helper(line3, line1, point2);
  get_intersection_helper(line1, line2, point3);
  side_a = sqrt((point2[0] - point3[0]) * (point2[0] - point3[0]) + (point2[1] - point3[1]) * (point2[1] - point3[1]));
  side_b = sqrt((point3[0] - point1[0]) * (point3[0] - point1[0]) + (point3[1] - point1[1]) * (point3[1] - point1[1]));
  side_c = sqrt((point1[0] - point2[0]) * (point1[0] - point2[0]) + (point1[1] - point2[1]) * (point1[1] - point2[1]));
}
