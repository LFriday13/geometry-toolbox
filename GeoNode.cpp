/*
 * Geonode.cpp
 *
 */

#include "GeoNode.h"

GeoNode::GeoNode(int num_parents): num_parents(num_parents) {}

GeoNode::~GeoNode() {
	if (num_parents != 0)
		delete [] parents;
}
