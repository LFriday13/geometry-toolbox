/*
 * TriangleCentersNode.h
 *
 */

#ifndef TRIANGLECENTERSNODE_H_
#define TRIANGLECENTERSNODE_H_

#include "GeoNode.h"

enum TriangleCentersType {
	CENTROID,
  INCENTER
};

class TriangleCentersNode: public GeoNode {
  friend class TriangleCentersNode;
	double barycoeff_a, barycoeff_b, barycoeff_c;
	void (TriangleCentersNode::*definition)() {nullptr};
	virtual void print() const override;
	virtual void display() const override;
	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;
	virtual void update() override;

	void centroid();
	void incenter();
public:
  TriangleCentersNode();
	TriangleCentersNode(TriangleCentersType type,GeoNode* geo1);
	virtual ~TriangleCentersNode();
};

#endif /* TRIANGLECENTERSNODE_H_ */
