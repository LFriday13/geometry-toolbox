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
	POINT_POINT_POINT_CENTER_RADIUS,
};

class CircleNode: public GeoNode {

public:
	CircleNode();
	CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2);
	CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3);

	virtual ~CircleNode();

private:
	double center_x{0}, center_y{0}, radius{0};
    QCPItemEllipse *circle {nullptr};

	virtual void print() const override;
    virtual void display(Ui::MainWindow* ui) override;
    virtual void labels(vector<string>*, vector<string>*, vector<string>*) const override;

	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;

	virtual void update() override;
	void (CircleNode::*definition)() {nullptr};

	void point_point_point_through();
	void point_point_point_center_radius();
	void point_point_center_through();

};

#endif /* CIRCLENODE_H_ */
