/*
 * Geonode.cpp
 *
 */

#include "GeoNode.h"

GeoNode::GeoNode(int num_parents): num_parents(num_parents) {}

bool GeoNode::is_well_defined() const {
	return well_defined;
}

GeoNodeType GeoNode::get_type() const {
	return type;
}

string GeoNode::get_label() const {
	return label;
}

GeoNode::~GeoNode() {
	if (num_parents != 0)
		delete [] parents;
}
