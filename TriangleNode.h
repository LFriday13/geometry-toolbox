/*
 * TriangleNode.h
 *
 */

#ifndef TRIANGLENODE_H_
#define TRIANGLENODE_H_

#include "GeoNode.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

enum class TriangleType {
    POINT_POINT_POINT_VERTICES
};

class TriangleNode: public GeoNode {
public:
    TriangleNode();
	TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3);
    virtual ~TriangleNode() override;

private:
    double side_a {0}, side_b {0}, side_c {0};
    void (TriangleNode::*definition)() {nullptr};
    QCPCurve *triangle {nullptr};

    virtual void print() const override;
    virtual void display(Ui::MainWindow *ui) override;
    virtual void access(double data[]) const override;
    virtual void mutate(double data[]) override;
    virtual void update() override;
    virtual void labels(vector<string>*, vector<string>*, vector<string>*, vector<string>*) const override;

    void point_point_point_vertices();
};

#endif /* TRIANGLENODE_H_ */
