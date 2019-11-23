/*
 * GeoNode.h
 *
 */

#ifndef GEONODE_H_
#define GEONODE_H_

#include <iostream>
using namespace std;

class GeoNode {
	friend class GeoComponents;

public:
	GeoNode(int num_parents = 0);
	virtual ~GeoNode();

	virtual void access(double data[]) const = 0;
	string get_label() const;
	
private:
	virtual void display() const = 0;
	virtual void print() const = 0;
	virtual void mutate(double data[]) = 0;
	virtual void update() = 0;

	unsigned int pid {0};
	string label {""};
	bool need_display {true};

protected:
	const int num_parents {0};
	const GeoNode** parents {nullptr};
	bool well_defined {true};

};

#endif /* GEONODE_H_ */
