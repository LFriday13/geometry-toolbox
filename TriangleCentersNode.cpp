/*
 * TriangleCentersNode.cpp
 *
 */
#include <math.h>
#include "TriangleCentersNode.h"

TriangleCentersNode::TriangleCentersNode() {}

TriangleCentersNode::TriangleCentersNode(TriangleCentersType type, GeoNode* geo1): GeoNode(1) {
  switch(type) {
		case CENTROID: definition = &TriangleCentersNode::centroid; break;
		case INCENTER: definition = &TriangleCentersNode::incenter; break;
    case CIRCUMCENTER: definition = &TriangleCentersNode::circumcenter; break;
    case ORTHOCENTER: definition = &TriangleCentersNode::orthocenter; break;
    case NINEPOINTCENTER: definition = &TriangleCentersNode::ninepointcenter; break;
    case SYMMEDIAN: definition = &TriangleCentersNode::symmedian; break;
	}
  parents = new const GeoNode*[num_parents];
	parents[0] = geo1;
  (this->*definition)();
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

void TriangleCentersNode::display() const {

}

void TriangleCentersNode::access(double data[]) const {
  data[0] = barycoeff_a;
  data[1] = barycoeff_b;
  data[2] = barycoeff_c;
}

void TriangleCentersNode::mutate(double data[]) {
  barycoeff_a = data[0];
  barycoeff_b = data[1];
  barycoeff_c = data[2];
  if(barycoeff_a * barycoeff_a + barycoeff_b * barycoeff_b + barycoeff_c * barycoeff_c < 1e-8 )
    well_defined = false;
  else well_defined = true;
  (this->*definition)();
}

void TriangleCentersNode::update() {
  (this->*definition)();
}

TriangleCentersNode::~TriangleCentersNode() {}

void TriangleCentersNode::centroid() {
  barycoeff_a = barycoeff_b = barycoeff_c = 1;
  well_defined = true;
}

void TriangleCentersNode::incenter() {
  double triangle[3];
  parents[0]->access(triangle);
  barycoeff_a = triangle[0];
  barycoeff_b = triangle[1];
  barycoeff_c = triangle[2];
  well_defined = true;
}

void TriangleCentersNode::circumcenter() {
  double triangle[3], barycoeff[3];
  parents[0]->access(triangle);
  for(int i = 0; i < 3; i++){
    barycoeff[i] = triangle[i] * triangle[i] * (triangle[(i+1)%3] * triangle[(i+1)%3] + triangle[(i+2)%3] * triangle[(i+2)%3] - triangle[i%3] * triangle[i%3]);
  }
  barycoeff_a = barycoeff[0];
  barycoeff_b = barycoeff[1];
  barycoeff_c = barycoeff[2];
  well_defined = true;
}

void TriangleCentersNode::orthocenter() {
  double triangle[3], barycoeff[3];
  parents[0]->access(triangle);
  double sum = triangle[0] * triangle[0] + triangle[1] * triangle[1] + triangle[2] * triangle[2];
  for(int i = 0; i < 3; i++)
  {
    if(abs(triangle[i] * triangle[i] * 2 - sum) < 1e-8)
    {
      for(int j = 0; j < 3; j++)barycoeff[j] = 0.0;
      barycoeff[i] = 1.0;
      break;
    }
  }
  barycoeff_a = barycoeff[0];
  barycoeff_b = barycoeff[1];
  barycoeff_c = barycoeff[2];
  well_defined = true;
}

void TriangleCentersNode::ninepointcenter() {
  double triangle[3];
  parents[0]->access(triangle);
  for(int i = 0; i < 3; i++) triangle[i] *= triangle[i];
  barycoeff_a = triangle[0] * (triangle[1] + triangle[2]) + (triangle[1] - triangle[2]) * (triangle[1] - triangle[2]);
  barycoeff_b = triangle[1] * (triangle[2] + triangle[0]) + (triangle[2] - triangle[0]) * (triangle[2] - triangle[0]);
  barycoeff_c = triangle[2] * (triangle[0] + triangle[1]) + (triangle[0] - triangle[1]) * (triangle[0] - triangle[1]);
  well_defined = true;
}

void TriangleCentersNode::symmedian() {
  double triangle[3];
  parents[0]->access(triangle);
  barycoeff_a = triangle[0] * triangle[0];
  barycoeff_b = triangle[1] * triangle[1];
  barycoeff_c = triangle[2] * triangle[2];
  well_defined = true;
}
