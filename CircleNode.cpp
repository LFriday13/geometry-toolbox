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

void CircleNode::display(Ui::MainWindow *ui) {
    if(!need_display) return;

    if(circle == nullptr){ //Initialization
        circle = new QCPItemEllipse(ui->custom_plot);
        circle->setAntialiased(true);
        circle->setPen(QPen(QColor(120, 120, 120), 2));
    }

    circle->topLeft->setCoords(center_x-radius, center_y+radius);
    circle->bottomRight->setCoords(center_x+radius, center_y-radius);
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
	
	double distance = p3[0]*(p1[1] - p2[1]) + p3[1]*(p2[0] - p1[0]) - (p1[0]*(p1[1] - p2[1]) + p1[1]*(p2[0] - p1[0]));
	
	if(distance < std::numeric_limits<double>::epsilon() && distance > -std::numeric_limits<double>::epsilon()) {
		well_defined = false;
		
	} else {
		double x1=p1[0], x2=p2[0], x3=p3[0];
		double y1=p1[1], y2=p2[1], y3=p3[1];

		
		double x12 = x1 - x2, x13 = x1 - x3, x31 = x3 - x1, x21 = x2 - x1;
		double y12 = y1 - y2, y13 = y1 - y3, y31 = y3 - y1, y21 = y2 - y1;

		double sx13 = x1*x1 - x3*x3, sx21 = x2*x2 - x1*x1;
		double sy13 = y1*y1 - y3*y3, sy21 = y2*y2 - y1*y1;

		center_y = (-1)*((sx13) * (x12) + (sy13) * (x12) + (sx21) * (x13) + (sy21) * (x13));
		center_y /= (2 * ((y31) * (x12) - (y21) * (x13)));

		center_x = (-1)*((sx13) * (y12) + (sy13) * (y12)  + (sx21) * (y13) + (sy21) * (y13));
		center_x /= (2 * ((x31) * (y12) - (x21) * (y13)));

		radius = sqrt((center_x - x1)*(center_x - x1) + (center_y - y1)*(center_y - y1));
		
	}
}

void CircleNode::point_point_center_through(){
	double p1[2], p2[2];
	parents[0]->access(p1);
	parents[1]->access(p2);
	
	double distance = sqrt((p2[0] - p1[0])*(p2[0] - p1[0]) + (p2[1] - p1[1])*(p2[1] - p1[1]));
	
	if(distance < std::numeric_limits<double>::epsilon() && distance > -std::numeric_limits<double>::epsilon()) {
		well_defined = false;	
	} else {
		center_x = p1[0];
		center_y = p1[1];
		radius = distance;
	}
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
