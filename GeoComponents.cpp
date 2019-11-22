/*
 * GeoComponents.cpp
 *
 */

#include "GeoComponents.h"

GeoComponents::GeoComponents() {}

void GeoComponents::add_construction(){
	//TODO
}

void GeoComponents::edit_construction(unsigned int PID, double data[]){ 
	bool mutated = false; 
	auto it = begin(geo_components); //STL iterator
	
	//Locates the element we want to edit
	for (; it != end(geo_components); ++it){ 
		if((*it)->pid == PID){
			if(!(*it)->user_defined){
				cout << "The construction is not user defined." << endl;
				return;
			}
			(*it)->mutate(data);
			mutated = true;
			++it;
			break;
		}
	}
	
	//Updates every element after the mutated one (innefficient)
	for (; it != end(geo_components); ++it){ 
		(*it)->update();
	}
	
	//Standard error message
	if (mutated) {cout << "Mutated construction " << PID << " succesfully." << endl;}
	else {cout << "The construction does not exists." << endl;}
}

void GeoComponents::remove_construction(unsigned int PID){
	//TODO
}

void GeoComponents::print_all_constructions(){
	for (auto it = begin(geo_components); it != end(geo_components); ++it){
		(*it)->print();
	}
}


void GeoComponents::display_all_constructions(){
	for (auto it = begin(geo_components); it != end(geo_components); ++it){
		if((*it)->need_display){(*it)->display();}
	}
}

GeoComponents::~GeoComponents() {
	while(!geo_components.empty()) {
        	delete geo_components.back();
        	geo_components.pop_back();
	}
}
