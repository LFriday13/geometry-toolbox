/*
 * TriangleNode.h
 *
 */

#ifndef TRIANGLENODE_H_
#define TRIANGLENODE_H_

#include "GeoNode.h"

class TriangleNode: public GeoNode {
	double side_a, side_b, side_c;
	void (*construct)();
	virtual void print() const override;
	virtual void display() const override;
	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;
	virtual void update() override;
public:
	TriangleNode();
	virtual ~TriangleNode();
};

#endif /* TRIANGLENODE_H_ */
