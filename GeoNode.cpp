/*
 * Geonode.cpp
 *
 */

#include "GeoNode.h"

GeoNode::GeoNode() {}

GeoNode::~GeoNode() {
	if (num_parents != 0)
		delete [] parents;
}
