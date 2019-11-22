/*
 * Geonode.h
 *
 */

#ifndef GEONODE_H_
#define GEONODE_H_
#include <iostream>
using namespace std;

class GeoNode {

public:
	GeoNode();
	friend class GeoComponents;
	
	virtual ~GeoNode();
	
private:
	virtual void display() const = 0;
	virtual void print() const = 0;
	virtual void access(double data[]) const = 0;
	virtual void mutate(double data[]) = 0;
	virtual void update() = 0;
	
protected: 
	unsigned int pid;
	bool user_defined;
	bool hidden;
	string label;
	const int num_parents;
	const GeoNode** parents;
	
};

#endif /* GEONODE_H_ */
