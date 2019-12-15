/*
 * TriangleNode.cpp
 *
 */
#include <cmath>
#include "TriangleNode.h"

TriangleNode::TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3): GeoNode(3) {

    // Identification of definition from TriangleType
    switch(type) {
    case TriangleType::POINT_POINT_POINT_VERTICES: definition = &TriangleNode::point_point_point_vertices; break;
    default: well_defined = false; return;
    }

    // Initialization of Data Members
    parents = new const GeoNode*[num_parents];
    parents[0] = geo1;
    parents[1] = geo2;
    parents[2] = geo3;
    (this->*definition)();
}

void TriangleNode::print() const {
    cout << "----------------------------------------\n";
    cout << "Identifier: " << this->get_label() << endl;
    cout << "Data: " << side_a << '\t' << side_b << '\t' << side_c << endl;
    cout << "Parents:";
    for(int i = 0; i < num_parents;++i)
        cout << " " << parents[i]->get_label();
    cout << endl;
}

void TriangleNode::display(Ui::MainWindow *ui) {
    if(triangle == nullptr){
        triangle = new QCPCurve(ui->custom_plot->xAxis, ui->custom_plot->yAxis);
        triangle->setPen(Qt::NoPen);
        triangle->setBrush(QColor(10, 100, 50, 160));
        triangle->setLayer("main");
        triangle->setName(QString::fromStdString(this->get_label()));
    }

    triangle->setVisible(well_defined);
    double p1[2], p2[2], p3[2];
    parents[0]->access(p1);
    parents[1]->access(p2);
    parents[2]->access(p3);

    triangle->data()->clear();
    triangle->addData(p1[0],p1[1]);
    triangle->addData(p2[0],p2[1]);
    triangle->addData(p3[0],p3[1]);
    triangle->addData(p1[0],p1[1]);
}

void TriangleNode::access(double data[]) const {
    double point1[2], point2[2], point3[2];
    parents[0]->access(point1);
    parents[1]->access(point2);
    parents[2]->access(point3);
    data[0] = point1[0];
    data[1] = point1[1];
    data[2] = point2[0];
    data[3] = point2[1];
    data[4] = point3[0];
    data[5] = point3[1];
    data[6] = side_a;
    data[7] = side_b;
    data[8] = side_c;
}

void TriangleNode::mutate(double data[]) {
    side_a = data[0];
    side_b = data[1];
    side_c = data[2];
    (this->*definition)();
}

void TriangleNode::update() {
    (this->*definition)();
}

TriangleNode::~TriangleNode() {
    if(triangle != nullptr)
        (triangle->parentPlot())->removePlottable(triangle);
}

void TriangleNode::point_point_point_vertices() {

    // Data Access
    double point1[2], point2[2], point3[2];
    parents[0]->access(point1);
    parents[1]->access(point2);
    parents[2]->access(point3);

    // Mathematical Formula
    side_a = sqrt((point2[0] - point3[0]) * (point2[0] - point3[0]) + (point2[1] - point3[1]) * (point2[1] - point3[1]));
    side_b = sqrt((point3[0] - point1[0]) * (point3[0] - point1[0]) + (point3[1] - point1[1]) * (point3[1] - point1[1]));
    side_c = sqrt((point1[0] - point2[0]) * (point1[0] - point2[0]) + (point1[1] - point2[1]) * (point1[1] - point2[1]));

    well_defined = (side_a > EPSILON && side_b > EPSILON && side_c > EPSILON);
}

void TriangleNode::labels(vector<string> *, vector<string> *, vector<string> *, vector<string> *triangle_labels) const {
    triangle_labels->push_back(this->get_label());
}
