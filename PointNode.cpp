/*
 * PointNode.cpp
 *
 */

#include <cmath>
#include <limits>
#include "PointNode.h"

PointNode::PointNode() {}

PointNode::PointNode(PointType type, double x, double y) : x(x), y(y), definition(&PointNode::independent) {}

PointNode::PointNode(PointType type, GeoNode* geo1, double x, double y) : GeoNode(1) {

    switch(type) {
        case ON_LINE: definition = &PointNode::on_line; break;
        case ON_CIRCLE:	definition = &PointNode::on_circle; break;
    }

    parents = new const GeoNode*[num_parents];
    parents[0] = geo1;
    this->x = x;
    this->y = y;
    (this->*definition)();
}

PointNode::PointNode(PointType type, GeoNode* geo1, GeoNode* geo2) : GeoNode(2) {

    switch(type) {
        case POINT_POINT_MIDPOINT: definition = &PointNode::point_point_midpoint; break;
        case LINE_LINE_INTERSECTION: definition = &PointNode::line_line_intersection; break;
        case LINE_CIRCLE_FIRST_INTERSECTION: definition = &PointNode::line_circle_first_intersection; break;
        case LINE_CIRCLE_SECOND_INTERSECTION: definition = &PointNode::line_circle_second_intersection; break;
        case CIRCLE_CIRCLE_FIRST_INTERSECTION: definition = &PointNode::circle_circle_first_intersection; break;
        case CIRCLE_CIRCLE_SECOND_INTERSECTION: definition = &PointNode::circle_circle_second_intersection; break;
    }

    parents = new const GeoNode*[num_parents];
    parents[0] = geo1;
    parents[1] = geo2;
    (this->*definition)();
}

PointNode::~PointNode() {}

void PointNode::print() const {
    cout << "----------------------------------------\n";
    cout << "Identifier: " << this->get_label() << endl;
    cout << "Data: " << x << '\t' << y << endl;
    cout << "Parents:";
    for(int i = 0; i < num_parents;++i)
        cout << " " << parents[i]->get_label();
    cout << endl;
}

void PointNode::display() const {
    //TODO
}

void PointNode::access(double data[]) const {
    data[0] = x;
    data[1] = y;
}

void PointNode::mutate(double data[]) {
    x = data[0];
    y = data[1];
    (this->*definition)();
}

void PointNode::update() {
    (this->*definition)();
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
    x = circle[0] + (x - circle[0]) * circle[2] / current_radius;
    y = circle[1] + (y - circle[1]) * circle[2] / current_radius;
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
    if(delta < std::numeric_limits<double>::epsilon() && delta > -std::numeric_limits<double>::epsilon())
        well_defined = false;
    else{
        delta_x = line1[2] * line2[1] - line1[1] * line2[2];
        delta_y = line1[0] * line2[2] - line1[2] * line2[0];
        x = delta_x / delta;
        y = delta_y / delta;
    }
}

void PointNode::line_circle_first_intersection() {
    //TODO
    //If the line does not intersect the circle, set well-defined as false
    //Otherwise, calculate normally, prefering the solution with a higher y
    //If the y's are too close, prefer the one with the higher x
}

void PointNode::line_circle_second_intersection() {
    //TODO
    //If the line does not intersect the circle at a second time, set well-defined as false
    //Otherwise, calculate normally, prefering the solution with a higher y
    //If the y's are too close, prefer the one with the higher x
}

void PointNode::circle_circle_first_intersection() {
    //TODO
    //If the circles do not intersect, set well-defined as false
    //Otherwise, calculate normally, prefering the solution with a higher y
    //If the y's are too close, prefer the one with the higher x
}

void PointNode::circle_circle_second_intersection() {
    //TODO
    //TODO
    //If the circles do not intersect at a second time, set well-defined as false
    //Otherwise, calculate normally, prefering the solution with a higher y
    //If the y's are too close, prefer the one with the higher x
}
