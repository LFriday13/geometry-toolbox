/*
 * LineNode.h
 *
 */

#ifndef LINENODE_H_
#define LINENODE_H_

#include "GeoNode.h"

enum LineType {
	POINT_POINT_LINE_THROUGH,
	POINT_LINE_PARALLEL_LINE_THROUGH,
	POINT_POINT_PERPENDICULAR_BISECTOR,
	POINT_CIRCLE_HIGHER_TANGENT,
	POINT_CIRCLE_LOWER_TANGENT
};

class LineNode: public GeoNode {

public:
	LineNode();
	LineNode(LineType type, GeoNode* geo1, GeoNode* geo2);

	virtual ~LineNode();

private:
	double x_coeff{0}, y_coeff{0}, c_coeff{0};

	virtual void print() const override;
	virtual void display() const override;

	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;

	virtual void update() override;
	void (LineNode::*definition)() {nullptr};

	void point_point_line_through();
	void point_line_parallel_line_through();
	void point_point_perpendicular_bisector();
	void point_circle_higher_tangent();
	void point_circle_lower_tangent();

};

#endif /* LINENODE_H_ */
