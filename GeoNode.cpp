/*
 * Geonode.cpp
 *
 */

#include "GeoNode.h"

GeoNode::GeoNode(int num_parents): num_parents(num_parents) {}

string GeoNode::get_label() const {
	return label;
}

GeoNode::~GeoNode() {
	if (num_parents != 0)
		delete [] parents;
}
