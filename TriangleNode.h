/*
 * TriangleNode.h
 *
 */

#ifndef TRIANGLENODE_H_
#define TRIANGLENODE_H_

#include "GeoNode.h"

enum TriangleType {
	POINT_POINT_POINT_VERTICES,
  LINE_LINE_LINE_INTERSECTIONS
};

class TriangleNode: public GeoNode {
	double side_a, side_b, side_c;
	void (TriangleNode::*definition)() {nullptr};
	virtual void print() const override;
	virtual void display() const override;
	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;
	virtual void update() override;

  void point_point_point_vertices();
  void line_line_line_intersections();
public:
  TriangleNode();
	TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3);
	virtual ~TriangleNode();
};

#endif /* TRIANGLENODE_H_ */
