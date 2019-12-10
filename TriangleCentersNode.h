/*
 * TriangleCentersNode.h
 *
 */

#ifndef TRIANGLECENTERSNODE_H_
#define TRIANGLECENTERSNODE_H_

#include "GeoNode.h"

enum class TriangleCentersType {
    CENTROID,
    INCENTER,
    CIRCUMCENTER,
    ORTHOCENTER,
    NINEPOINTCENTER,
    SYMMEDIAN
};

class TriangleCentersNode: public GeoNode {

public:
    TriangleCentersNode();
    TriangleCentersNode(TriangleCentersType type,GeoNode* geo1);
    virtual ~TriangleCentersNode() override;

private:
    double barycoeff_a {0}, barycoeff_b {0}, barycoeff_c {0};
    QCPGraph *center {nullptr};

    void (TriangleCentersNode::*definition)() {nullptr};

    virtual void print() const override;
    virtual void display(Ui::MainWindow *ui) override;
    virtual void access(double data[]) const override;
    virtual void mutate(double data[]) override;
    virtual void update() override;
    virtual void labels(vector<string>*, vector<string>*, vector<string>*, vector<string>*) const override;

    void cartesian(double data []) const;

    void centroid();
    void incenter();
    void circumcenter();
    void orthocenter();
    void ninepointcenter();
    void symmedian();

};

#endif /* TRIANGLECENTERSNODE_H_ */
