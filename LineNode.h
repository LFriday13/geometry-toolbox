/*
 * LineNode.h
 *
 */

#ifndef LINENODE_H_
#define LINENODE_H_

#include "GeoNode.h"

class LineNode: public GeoNode {
	double x_coeff, y_coeff, c_coeff;
	void (*construct)();
	virtual void print() const override;
	virtual void print_GUI() const override;
	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;
	virtual void update() override;
public:
	LineNode();
	virtual ~LineNode();
};

#endif /* LINENODE_H_ */
