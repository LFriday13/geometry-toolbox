/*
 * GeoComponents.h
 *
 */

#ifndef GEOCOMPONENTS_H_
#define GEOCOMPONENTS_H_

#include <vector>
#include "GeoNode.h"

class GeoComponents {

	vector <GeoNode*> geo_components;
public:
	void add_construction();
	void edit_construction(unsigned int PID, double data[]);
	void remove_construction(unsigned int PID);
	void print_all_constructions();
	void display_all();
	GeoComponents();

	virtual ~GeoComponents();
	
};

#endif /* GEOCOMPONENTS_H_ */
