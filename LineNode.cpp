/*
 * LineNode.cpp
 *
 */

#include <cmath>
#include "LineNode.h"

LineNode::LineNode(LineType type, GeoNode* geo1, GeoNode* geo2) : GeoNode(2) {

    // Identification of definition from LineType
    switch(type) {
    case LineType::POINT_POINT_LINE_THROUGH: definition = &LineNode::point_point_line_through; break;
    case LineType::POINT_LINE_PARALLEL_LINE_THROUGH: definition = &LineNode::point_line_parallel_line_through; break;
    case LineType::POINT_POINT_PERPENDICULAR_BISECTOR: definition = &LineNode::point_point_perpendicular_bisector; break;
    case LineType::POINT_CIRCLE_FIRST_TANGENT: definition = &LineNode::point_circle_first_tangent; break;
    case LineType::POINT_CIRCLE_SECOND_TANGENT: definition = &LineNode::point_circle_second_tangent; break;
    default: well_defined = false; return;
    }

    // Initialization of Data Members
    parents = new const GeoNode*[num_parents];
    parents[0] = geo1;
    parents[1] = geo2;

    update();
}

LineNode::~LineNode() {
    if(line != nullptr)
        (line->parentPlot())->removeItem(line);
}

void LineNode::print() const {
    cout << "----------------------------------------\n";
    cout << "Identifier: " << this->get_label() << endl;
    cout << "Data: " << x_coeff << '\t' << y_coeff << '\t' << c_coeff << endl;
    cout << "Parents:";
    for(int i = 0; i < num_parents;++i)
        cout << " " << parents[i]->get_label();
    cout << endl;
}

void LineNode::display(Ui::MainWindow *ui) {
    if(line == nullptr){ //Initialization
        line = new QCPItemStraightLine(ui->custom_plot);
        line->setPen(QPen(QColor(120, 120, 120), 2));
        line->setObjectName(QString::fromStdString(this->get_label()));
    }

    line->setVisible(well_defined);
    (abs(y_coeff) > EPSILON) ? line->point1->setCoords(0, - c_coeff/y_coeff): line->point1->setCoords(-c_coeff/x_coeff, 1);
    (abs(x_coeff) > EPSILON) ? line->point2->setCoords(- c_coeff/x_coeff, 0): line->point2->setCoords(1, - c_coeff/y_coeff);
}

void LineNode::access(double data[]) const {
    data[0] = x_coeff;
    data[1] = y_coeff;
    data[2] = c_coeff;
}

void LineNode::mutate(double data[]) {
    x_coeff = data[0];
    y_coeff = data[1];
    c_coeff = data[2];
    update();
}

void LineNode::update() {
    well_defined = true;
    for (int i = 0; i < num_parents; ++i)
        well_defined &= parents[i]->get_well_defined();
    if (well_defined)
        (this->*definition)();
}

void LineNode::point_point_line_through() {

    // Data Access
    double p1[2], p2[2];
    parents[0]->access(p1);
    parents[1]->access(p2);

    // Mathematical Formula
    x_coeff = p1[1] - p2[1];
    y_coeff = p2[0] - p1[0];

    if(x_coeff < EPSILON && x_coeff > -EPSILON) {
        if(y_coeff < EPSILON && y_coeff > -EPSILON)
            well_defined = false;
    } else {
        c_coeff = (-y_coeff)*p1[1] + (-x_coeff)*p1[0];

        well_defined = true;
    }
}

void LineNode::point_line_parallel_line_through() {

    // Data Access
    double point[2], line[3];
    parents[0]->access(point);
    parents[1]->access(line);

    // Mathematical Formula
    x_coeff = line[0];
    y_coeff = line[1];
    c_coeff = (-y_coeff)*point[1] + (-x_coeff)*point[0];
}

void LineNode::point_point_perpendicular_bisector() {

    // Data Access
    double p1[2], p2[2];
    parents[0]->access(p1);
    parents[1]->access(p2);

    // Mathematical Formula
    x_coeff = p2[0] - p1[0];
    y_coeff = p2[1] - p1[1];
    c_coeff = (-x_coeff)*(p1[0] + p2[0])/2 + (-y_coeff)*(p1[1] + p2[1])/2;
    well_defined = (abs(x_coeff) + abs(y_coeff) > EPSILON);
}

void LineNode::point_circle_first_tangent() {

    // Data Access
    double point[2], circle[3];
    parents[0]->access(point);
    parents[1]->access(circle);

    // Mathematical Formula
    double distance = sqrt((point[0] - circle[0]) * (point[0] - circle[0]) + (point[1] - circle[1]) * (point[1] - circle[1]));

    if(distance - circle[2] < EPSILON && distance - circle[2] > -EPSILON) {
        x_coeff = point[0] - circle[0];
        y_coeff = point[1] - circle[1];
        c_coeff = (-x_coeff)*point[0] + (-y_coeff)*point[1];

        well_defined = true;

    } else if(distance < circle[2]) {
        well_defined = false;

    } else {
        //Let the line be: (y-point_y)=k(x-point_x)
        double sk_coeff, k_coeff, c, k;

        //Define variables for simplicity
        double delta_x, delta_y, radius;
        delta_x = circle[0] - point[0];
        delta_y = point[1] - circle[1];
        radius = circle[2];

        //Compute the coefficients of the quadratic
        sk_coeff = delta_x*delta_x - radius*radius;
        k_coeff = 2*delta_x*delta_y;
        c = delta_y*delta_y - radius*radius;

        //Solve for the slope
        if(abs(sk_coeff) < EPSILON) {
            x_coeff = 1;
            y_coeff = 0;
            c_coeff = -point[0];

        } else {
            k = (-k_coeff + sqrt(k_coeff*k_coeff - 4*sk_coeff*c))/(2*sk_coeff);
            x_coeff = k;
            y_coeff = -1;
            c_coeff = -k*point[0] + point[1];
        }

        well_defined = true;
    }
}

void LineNode::point_circle_second_tangent() {

    // Data Access
    double point[2], circle[3];
    parents[0]->access(point);
    parents[1]->access(circle);

    // Mathematical Formula
    double distance = sqrt((point[0] - circle[0]) * (point[0] - circle[0]) + (point[1] - circle[1]) * (point[1] - circle[1]));

    if(distance - circle[2] < EPSILON && distance - circle[2] > -EPSILON) {
        well_defined = false;

    } else if(distance < circle[2]) {
        well_defined = false;

    } else {
        //Let the line be: (y-point_y)=k(x-point_x)
        double sk_coeff, k_coeff, c, k;

        //Define variables for simplicity
        double delta_x, delta_y, radius;
        delta_x = circle[0] - point[0];
        delta_y = point[1] - circle[1];
        radius = circle[2];

        //Compute the coefficients of the quadratic
        sk_coeff = delta_x*delta_x - radius*radius;
        k_coeff = 2*delta_x*delta_y;
        c = delta_y*delta_y - radius*radius;

        if(abs(sk_coeff) < EPSILON) {
            // Linear case
            k = -c/k_coeff;
            x_coeff = k;
            y_coeff = -1;
            c_coeff = -k*point[0] + point[1];

        } else {
            //Solve for the slope
            k = (-k_coeff - sqrt(k_coeff*k_coeff - 4*sk_coeff*c))/(2*sk_coeff);
            x_coeff = k;
            y_coeff = -1;
            c_coeff = -k*point[0] + point[1];
        }

        well_defined = true;

    }
}

void LineNode::labels(vector<string>*, vector<string>* line_labels, vector<string>*, vector<string>*) const {
    line_labels->push_back(this->get_label());
}
