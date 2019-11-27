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
	GeoComponents();
	virtual ~GeoComponents();

	void add_construction(GeoNode* geo);
	void edit_construction(unsigned int pid, double data[]);
    void remove_construction(unsigned int pid);
    void print_all_constructions();
    void display_all_constructions(Ui::MainWindow *ui);
    GeoNode* get_construction(unsigned int pid);

private:
	vector <GeoNode*> geo_components;
	unsigned int next_pid {0};
};

#endif /* GEOCOMPONENTS_H_ */
