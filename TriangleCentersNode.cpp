/*
 * TriangleCentersNode.cpp
 *
 */
#include <cmath>
#include "TriangleCentersNode.h"

TriangleCentersNode::TriangleCentersNode(TriangleCentersType type, GeoNode* geo1): GeoNode(1) {

    // Identification of definition from TriangleCentersType
    switch(type) {
    case TriangleCentersType::CENTROID: definition = &TriangleCentersNode::centroid; break;
    case TriangleCentersType::INCENTER: definition = &TriangleCentersNode::incenter; break;
    case TriangleCentersType::CIRCUMCENTER: definition = &TriangleCentersNode::circumcenter; break;
    case TriangleCentersType::ORTHOCENTER: definition = &TriangleCentersNode::orthocenter; break;
    case TriangleCentersType::NINEPOINTCENTER: definition = &TriangleCentersNode::ninepointcenter; break;
    case TriangleCentersType::LEMOINEPOINT: definition = &TriangleCentersNode::symmedian; break;
    default: well_defined = false; return;
    }

    // Initialization of Data Members
    parents = new const GeoNode*[num_parents];
    parents[0] = geo1;

    update();
}

void TriangleCentersNode::print() const {
    cout << "----------------------------------------\n";
    cout << "Identifier: " << this->get_label() << endl;
    cout << "Data: " << barycoeff_a << '\t' << barycoeff_b << '\t' << barycoeff_c << endl;
    cout << "Parents:";
    for(int i = 0; i < num_parents;++i)
        cout << " " << parents[i]->get_label();
    cout << endl;
}

void TriangleCentersNode::display(Ui::MainWindow *ui) {
    if(center == nullptr){ //Initialization
        center = ui->custom_plot->addGraph();
        center->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
        center->setPen(QPen(QColor(120, 120, 120), 2));
        center->setLayer("front");
        center->setName(QString::fromStdString(this->get_label()));
    }

    center->setVisible(well_defined);
    center->data()->clear();

    double coor[2];
    this->cartesian(coor);

    center->addData(coor[0], coor[1]);
}

void TriangleCentersNode::access(double data[]) const {
    this->cartesian(data);
}

void TriangleCentersNode::mutate(double data[]) {
    barycoeff_a = data[0];
    barycoeff_b = data[1];
    barycoeff_c = data[2];
    update();
}

void TriangleCentersNode::update() {
    well_defined = true;
    for (int i = 0; i < num_parents; ++i)
        well_defined &= parents[i]->get_well_defined();
    if (well_defined)
        (this->*definition)();
}

TriangleCentersNode::~TriangleCentersNode() {
    if(center != nullptr)
        (center->parentPlot())->removeGraph(center);
}

void TriangleCentersNode::centroid() {
    // Mathematical Formula
    barycoeff_a = barycoeff_b = barycoeff_c = 1;
}

void TriangleCentersNode::incenter() {

    // Data Access
    double triangle[9];
    parents[0]->access(triangle);

    // Mathematical Formula
    barycoeff_a = triangle[6];
    barycoeff_b = triangle[7];
    barycoeff_c = triangle[8];
}

void TriangleCentersNode::circumcenter() {

    // Data Access
    double triangle[9], barycoeff[3];
    parents[0]->access(triangle);

    // Mathematical Formula
    for(int i = 0; i < 3; ++i){
        barycoeff[i] = triangle[6+i]*triangle[6+i] *
                ( triangle[6+((i+1)%3)] * triangle[6+((i+1)%3)]
                + triangle[6+((i+2)%3)] * triangle[6+((i+2)%3)]
                - triangle[6+(i%3)] * triangle[6+(i%3)] );
    }

    barycoeff_a = barycoeff[0];
    barycoeff_b = barycoeff[1];
    barycoeff_c = barycoeff[2];
}

void TriangleCentersNode::orthocenter() {

    // Data Access
    double triangle[9], barycoeff[3];
    parents[0]->access(triangle);

    // Mathematical Formula
    double sum = triangle[6] * triangle[6] + triangle[7] * triangle[7] + triangle[8] * triangle[8];

    for (int i = 0; i < 3; ++i) {
        barycoeff[i] = sum - 2*triangle[6+i]*triangle[6+i];
        if (abs(barycoeff[i]) < EPSILON) {
            barycoeff[0] = barycoeff[1] = barycoeff[2] = 0;
            barycoeff[i] = 1;
        } else {
            barycoeff[i] = 1 / barycoeff[i];
        }
    }

    barycoeff_a = barycoeff[0];
    barycoeff_b = barycoeff[1];
    barycoeff_c = barycoeff[2];
}

void TriangleCentersNode::ninepointcenter() {

    // Data Access
    double triangle[9];
    parents[0]->access(triangle);

    // Mathematical Formula
    for(int i = 0; i < 3; ++i)
        triangle[6+i] *= triangle[6+i];

    barycoeff_a = triangle[6] * (triangle[7] + triangle[8]) + (triangle[7] - triangle[8]) * (triangle[7] - triangle[8]);
    barycoeff_b = triangle[7] * (triangle[8] + triangle[6]) + (triangle[8] - triangle[6]) * (triangle[8] - triangle[6]);
    barycoeff_c = triangle[8] * (triangle[6] + triangle[7]) + (triangle[6] - triangle[7]) * (triangle[6] - triangle[7]);
}

void TriangleCentersNode::symmedian() {

    // Data Access
    double triangle[9];
    parents[0]->access(triangle);

    // Mathematical Formula
    barycoeff_a = triangle[6] * triangle[6];
    barycoeff_b = triangle[7] * triangle[7];
    barycoeff_c = triangle[8] * triangle[8];
}

void TriangleCentersNode::cartesian(double coordinates []) const {

    // Data Access
    double triangle[9];
    parents[0]->access(triangle);

    // Mathematical Conversion Formula
    double sum = barycoeff_a + barycoeff_b + barycoeff_c;

    coordinates [0] = barycoeff_a * triangle[0] + barycoeff_b * triangle[2] + barycoeff_c * triangle[4];
    coordinates [0] /= sum;
    coordinates [1] = barycoeff_a * triangle[1] + barycoeff_b * triangle[3] + barycoeff_c * triangle[5];
    coordinates [1] /= sum;
}

void TriangleCentersNode::labels(vector<string>* point_labels, vector<string>*, vector<string>*, vector<string>*) const {
    point_labels->push_back(this->get_label());
}
