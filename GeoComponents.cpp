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

void GeoComponents::add_construction(GeoNode* geo, string label) {
    if (geo->well_defined) {
        geo->pid = next_pid++;
        geo->label = label;
        geo_components.push_back(geo);
    } else {
        delete geo;
    }
}

void GeoComponents::edit_construction(unsigned int pid, double data[]) {

    // Record for dependences
    bool* is_ancestor = new bool[next_pid];

    // Simultaneous loop through array and vector
    unsigned int i = 0;
    for (auto it = begin(geo_components); it != end(geo_components); ++it, ++i){

        if (i < pid) {
            is_ancestor[i] = false;

        } else if (i == pid) {
            is_ancestor[i] = true;
            (*it)->mutate(data);

        } else {
            is_ancestor[i] = false;

            // Check for dependence
            int num = (*it)->num_parents;
            for (int j = 0; j < num; ++j) {
                if (is_ancestor[(*it)->parents[j]->pid]) {
                    is_ancestor[i] = true;
                    break;
                }
            }

            // Update if dependent
            if (is_ancestor[i])
                (*it)->update();
        }
    }

    delete [] is_ancestor;
}

void GeoComponents::remove_construction(unsigned int pid) {

    // Record for dependences
    bool* is_ancestor = new bool[next_pid];

    // Simultaneous loop through array and vector for updating record
    unsigned int i = 0;
    for (auto it = begin(geo_components); it != end(geo_components); ++it, ++i) {

        if (i < pid) {
            is_ancestor[i] = false;

        } else if (i == pid) {
            is_ancestor[i] = true;

        } else {
            is_ancestor[i] = false;

            // Check for dependence
            int num = (*it)->num_parents;
            for (int j = 0; j < num; ++j) {
                if (is_ancestor[(*it)->parents[j]->pid]) {
                    is_ancestor[i] = true;
                    break;
                }
            }
        }
    }

    // Reverse simultaneous loop through array and vector for deleting nodes
    i = next_pid - 1;
    for (auto it = geo_components.rbegin(); it != geo_components.rend(); ++it, --i) {
        if (is_ancestor[i]) {
            delete (*it);
            geo_components.erase((it+1).base());
        }
    }

    delete [] is_ancestor;

    // Simultaneous loop through array and vector for updating pid's
    i = 0;
    for (auto it = begin(geo_components); it != end(geo_components); ++it, ++i)
        (*it)->pid = i;
    next_pid = geo_components.size();

}

void GeoComponents::display_all_constructions(Ui::MainWindow *ui){
    for (auto it = begin(geo_components); it != end(geo_components); ++it)
        (*it)->display(ui);
}

void GeoComponents::update_ui_labels(vector<string>* point_labels, vector<string>* line_labels, vector<string>* circle_labels, vector<string>* triangle_labels, bool undefined) {
    point_labels->clear();
    line_labels->clear();
    circle_labels->clear();
    triangle_labels->clear();

    for (auto it = begin(geo_components); it != end(geo_components); ++it){
        if((*it)->well_defined || undefined)
            (*it)->labels(point_labels, line_labels, circle_labels, triangle_labels);
    }
}

void GeoComponents::print_all_constructions(){
    for (auto it = begin(geo_components); it != end(geo_components); ++it){
        (*it)->print();
    }
}

unsigned int GeoComponents::get_pid(string label){
    for (auto it = begin(geo_components); it != end(geo_components); ++it){
        if((*it)->label == label)
            return (*it)->pid;
    }

    return static_cast<unsigned int>(-1);
}

GeoNode* GeoComponents::get_construction(unsigned int pid){
    for (auto it = begin(geo_components); it != end(geo_components); ++it){
        if((*it)->pid == pid)
            return (*it);
    }

    return nullptr;
}
