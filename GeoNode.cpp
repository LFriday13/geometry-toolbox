/*
 * Geonode.cpp
 *
 */

#include "GeoNode.h"

const double GeoNode::EPSILON = 1e-8;

GeoNode::GeoNode(int num_parents): num_parents(num_parents) {}

string GeoNode::get_label() const {
	return label;
}

GeoNode::~GeoNode() {
	if (num_parents != 0)
		delete [] parents;
}
