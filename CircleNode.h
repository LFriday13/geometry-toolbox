/*
 * CircleNode.h
 *
 */

#ifndef CIRCLENODE_H_
#define CIRCLENODE_H_

#include "GeoNode.h"

enum CircleType {
	POINT_POINT_POINT_THROUGH,
	POINT_POINT_CENTER_THROUGH,
	POINT_CENTER_RADIUS,
	INDEPENDENT_CIRCLE
};

class CircleNode: public GeoNode {

public:
	CircleNode();
	CircleNode(CircleType type, double center_x, double center_y, double radius);
	CircleNode(CircleType type, GeoNode* geo, double radius);
	CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2);

	virtual ~CircleNode();

private:
	double center_x{0}, center_y{0}, radius{0};

	virtual void print() const override;
	virtual void display() const override;

	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;

	virtual void update() override;
	void (CircleNode::*definition)() {nullptr};

	void point_point_point_through();
	void point_point_center_through();
	void point_center_radius();
	void independent();

};

#endif /* CIRCLENODE_H_ */
