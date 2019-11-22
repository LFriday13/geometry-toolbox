/*
 * GeoComponents.cpp
 *
 */

#include "GeoComponents.h"

GeoComponents::GeoComponents() {}

void GeoComponents::add_construction(GeoNode* add){
	//TODO
}

void GeoComponents::edit_construction(unsigned int PID, double data[]){ 
	bool mutated = false; 
	auto it = begin(geo_components); //STL iterator
	
	//Locates the element we want to edit
	for (; it != end(geo_components); ++it){ 
		if((*it)->pid == PID){
			if(!(*it)->user_defined){
				cerr << "The construction is not user defined." << endl;
				return;
			}
			(*(it++))->mutate(data);
			mutated = true;
			break;
		}
	}
	
	//Updates every element after the mutated one (innefficient)
	for (; it != end(geo_components); ++it){ 
		(*it)->update();
	}
	
	//Standard error message
	if (mutated) {cerr << "Mutated construction " << PID << " succesfully." << endl;}
	else {cerr << "The construction does not exists." << endl;}
}

void GeoComponents::remove_construction(unsigned int PID){
	bool removed = false; 
	vector <GeoNode*> family;
	auto it = begin(geo_components); //STL iterator
	
	//Locates the element we want to remove
	for (; it != end(geo_components); ++it){ 
		if((*it)->pid == PID){
			if(!(*it)->user_defined){
				cerr << "The construction is not user defined." << endl;
				return;
			}
			delete (*it);
			family.push_back(*it);
			geo_components.erase(it++);
			removed = true;
			break;
		}
	}
	
	//Checks every element after the deleted one (innefficient)
	for (; it != end(geo_components);){ 
		int num = (*it)->num_parents;
		const GeoNode* compare = nullptr;
		bool needs_delete = false;
		
		for(int i=0; i<num; ++i){
			compare = (*it)->parents[i];
			for(auto it2 = begin(family); it2 != end(family); ++it2){
				if(compare == *it2){
					needs_delete = true;
					break;
				}
			}
			if(needs_delete){break;}
		}
		
		if(needs_delete){
			delete (*it);
			family.push_back(*it);
			geo_components.erase(it++);
			continue;
		}
		
		++it;
	}
	
	//Standard error message
	if (removed) {cerr << "Deleted construction " << PID << " succesfully." << endl;}
	else {cerr << "The construction does not exists." << endl;}
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
