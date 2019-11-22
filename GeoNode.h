/*
 * Geonode.h
 *
 */

#ifndef GEONODE_H_
#define GEONODE_H_
#include <iostream>
using namespace std;

class GeoNode {
	unsigned int pid;
	bool user_defined;
	bool hidden;
	string label;
	const int num_dependences;
	const GeoNode** parents;
	virtual void display() const = 0;
	virtual void print() const = 0;
	virtual void access(double data[]) const = 0;
	virtual void mutate(double data[]) = 0;
	virtual void update() = 0;
public:
	GeoNode();
	virtual ~GeoNode();
	friend class GeoComponents;
};

#endif /* GEONODE_H_ */
