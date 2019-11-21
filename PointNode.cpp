/*
 * PointNode.cpp
 *
 */

#include "PointNode.h"

PointNode::PointNode() {
  // TODO
}

void PointNode::print() const {
  // TODO
}

void PointNode::print_GUI() const {
  //TODO
}

void PointNode::access(double value[]) const {
  value[0] = this->x;
  value[1] = this->y;
}

void PointNode::mutate() {
  // TODO
}

PointNode::~PointNode() {
  // TODO
}
/*
function name: line_line_intersection
property: mutator
parameters:
prm[0]: line 1 x-coefficient
prm[1]: line 1 y-coefficient
prm[2]: line 1 c-coefficient
prm[3]: line 2 x-coefficient
prm[4]: line 2 y-coefficient
prm[5]: line 2 c-coefficient
implementation sketch: Cramer's rule
*/
void line_line_intersection(double prm[]) {
  double delta, delta_x, delta_y;
  double x_coeff[2] = {prm[0], prm[3]};
  double y_coeff[2] = {prm[1], prm[4]};
  double c_coeff[2] = {prm[2], prm[5]};
  delta = x_coeff[0] * y_coeff[1] - x_coeff[1] * y_coeff[0];
  delta_x = c_coeff[0] * y_coeff[1] - c_coeff[1] * y_coeff[0];
  delta_y = x_coeff[0] * c_coeff[1] - x_coeff[1] * c_coeff[0];
  x = delta_x / delta;
  y = delta_y / delta;
}
