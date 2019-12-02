/*
 * TriangleNode.h
 *
 */

#ifndef TRIANGLENODE_H_
#define TRIANGLENODE_H_

#include "GeoNode.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

enum TriangleType {
    POINT_POINT_POINT_VERTICES
};

class TriangleNode: public GeoNode {
	double side_a, side_b, side_c;
	void (TriangleNode::*definition)() {nullptr};
    QCPCurve *triangle {nullptr};

    virtual void print() const override;
    virtual void display(Ui::MainWindow *ui) override;
	virtual void access(double data[]) const override;
	virtual void mutate(double data[]) override;
	virtual void update() override;
    virtual void labels(vector<string>*, vector<string>*, vector<string>*) const override;

    void point_point_point_vertices();

public:
    TriangleNode();
	TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3);
	virtual ~TriangleNode();
};

#endif /* TRIANGLENODE_H_ */
