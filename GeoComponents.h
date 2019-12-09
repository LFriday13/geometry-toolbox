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

    // Base
    void add_construction(GeoNode* geo, string label = "");
	void edit_construction(unsigned int pid, double data[]);
    void remove_construction(unsigned int pid);
    void print_all_constructions();

    // Ui Dedicated
    void display_all_constructions(Ui::MainWindow *ui);
    GeoNode* get_construction(unsigned int pid);
    void update_ui_labels(vector<string> *point_labels, vector<string> *line_labels, vector<string> *circle_labels, vector<string> *triangle_labels);
    int get_pid(string label);

private:
	vector <GeoNode*> geo_components;
	unsigned int next_pid {0};
};

#endif /* GEOCOMPONENTS_H_ */
