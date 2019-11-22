/*
 * GeoComponents.h
 *
 */

#ifndef GEOCOMPONENTS_H_
#define GEOCOMPONENTS_H_

#include <vector>
#include "GeoNode.h"

class GeoComponents {

public:
	void add_construction();
	void edit_construction(unsigned int PID, double data[]);
	void remove_construction(unsigned int PID);
	void print_all_constructions();
	void display_all_constructions();
	GeoComponents();

	virtual ~GeoComponents();
	
private:
	vector <GeoNode*> geo_components;
	
};

#endif /* GEOCOMPONENTS_H_ */
