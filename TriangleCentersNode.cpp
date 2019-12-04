/*
 * TriangleCentersNode.cpp
 *
 */
#include "TriangleCentersNode.h"

TriangleCentersNode::TriangleCentersNode() {}

TriangleCentersNode::TriangleCentersNode(TriangleCentersType type, GeoNode* geo1): GeoNode(1) {
  switch(type) {
		case CENTROID: definition = &TriangleCentersNode::centroid; break;
		case INCENTER: definition = &TriangleCentersNode::incenter; break;
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
