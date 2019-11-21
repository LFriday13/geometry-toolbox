/*
 * PointNode.h
 *
 */

#ifndef POINTNODE_H_
#define POINTNODE_H_

#include "GeoNode.h"

enum PointType {
	INDEPENDENT,
	ON_LINE,
	ON_CIRCLE,
	POINT_POINT_MIDPOINT,
	LINE_LINE_INTERSECTION,
	LINE_CIRCLE_INTERSECTION,
	CIRCLE_CIRCLE_HIGHER_INTERSECTION,
	CIRCLE_CIRCLE_LOWER_INTERSECTION
};

class PointNode: public GeoNode {

public:
	PointNode();
	PointNode(PointType type, double x, double y);
	PointNode(PointType type, GeoNode* geo1, double x, double y);
	PointNode(PointType type, GeoNode* geo1, GeoNode* geo2);

	virtual ~PointNode();

private:
	double x, y;

	virtual void print() const override;
	virtual void display() const override;

	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;

	virtual void update() override;
	void (*update_this)();

	void point_point_midpoint();
	void line_line_intersection();
	void line_circle_intersection();
	void circle_circle_higher_intersection();
	void circle_circle_lower_intersection();

};

#endif /* POINTNODE_H_ */
