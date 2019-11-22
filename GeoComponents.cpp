/*
 * GeoComponents.cpp
 *
 */

#include "GeoComponents.h"

GeoComponents::GeoComponents() {}

GeoComponents::~GeoComponents() {
	while(!geo_components.empty()) {
		delete geo_components.back();
		geo_components.pop_back();
	}
}

void GeoComponents::add_construction(GeoNode* geo) {
	geo->pid = next_pid++;
	geo_components.push_back(geo);
}

void GeoComponents::edit_construction(unsigned int pid, double data[]) {

	// Record for dependencies
	bool* is_child = new bool[next_pid];

	// Simultaneous loop through array and vector
	unsigned int i = 0;
	for (auto it = begin(geo_components); it != end(geo_components); ++it, ++i){

		if (i < pid) {
			is_child[i] = false;

		} else if (i == pid) {
			is_child[i] = true;
			(*it)->mutate(data);

		} else {
			is_child[i] = false;

			// Check for dependencies
			int num = (*it)->num_parents;
			for (int j = 0; j < num; ++j) {
				if (is_child[(*it)->parents[j]->pid]) {
					is_child[i] = true;
					break;
				}
			}

			if (is_child[i])
				(*it)->update();
		}
	}

	delete [] is_child;
}

void GeoComponents::remove_construction(unsigned int pid) {

	// Record for dependencies
	bool* is_child = new bool[next_pid];

	// Simultaneous loop through array and vector for updating record
	unsigned int i = 0;
	for (auto it = begin(geo_components); it != end(geo_components); ++it, ++i) {

		if (i < pid) {
			is_child[i] = false;

		} else if (i == pid) {
			is_child[i] = true;

		} else {
			is_child[i] = false;

			// Check for dependencies
			int num = (*it)->num_parents;
			for (int j = 0; j < num; ++j) {
				if (is_child[(*it)->parents[j]->pid]) {
					is_child[i] = true;
					break;
				}
			}
		}
	}

	// Reverse simultaneous loop through array and vector for deleting nodes
	unsigned int i = next_pid - 1;
	for (auto it = rbegin(geo_components); it != rend(geo_components); ++it, --i) {
		if (is_child[i]) {
			delete (*it);
			geo_components.erase((it+1).base());
		}
	}

	delete [] is_child;

}

void GeoComponents::print_all_constructions(){
	for (auto it = begin(geo_components); it != end(geo_components); ++it){
		(*it)->print();
	}
}


void GeoComponents::display_all_constructions(){
	for (auto it = begin(geo_components); it != end(geo_components); ++it){
		if((*it)->need_display)
			(*it)->display();
	}
}
