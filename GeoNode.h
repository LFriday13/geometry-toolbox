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
	GeoNode();
	virtual ~GeoNode();

	virtual void access(double data[]) const = 0;

	void set_pid(unsigned int pid);
	void set_label(string label);
	void toggle_display();
	void not_user_defined();

private:
	virtual void display() const = 0;
	virtual void print() const = 0;
	virtual void mutate(double data[]) = 0;
	virtual void update() = 0;

protected:
	unsigned int pid {0};
	string label {""};
	bool user_defined {true};
	bool need_display {true};

	const int num_parents {0};
	const GeoNode** parents {nullptr};

};

#endif /* GEONODE_H_ */
