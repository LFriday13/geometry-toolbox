#include "solver.h"
#include <random>
#include <vector>
using namespace std;

Solver::Solver(GeoComponents* component, GeoNode* answer) {
  srand(time(nullptr));
  target = answer;
}

bool Solver::check() {
  if(main_data.next_pid == 0) return false;
  vector<bool> invalid(main_data.next_pid);
  for(int j = 0; j < check_trial_time; j++) {
    for(int i = 0; i < main_data.next_pid; i++) {
      if(main_data.geo_components[i]->get_type() == POINT)
      {
        double data[2];
        data[0] = rand() / 100.0;
        data[1] = rand() / 100.0;
        main_data.geo_components[i]->mutate(data);
        if(&main_data.geo_components[i] == &target) continue;
        invalid[i] = 1;
      }
      else
      {
        double data[3];
        data[0] = rand() / 100.0;
        data[1] = rand() / 100.0;
        data[2] = rand() / 100.0;
        main_data.geo_components[i]->mutate(data);
        if(&main_data.geo_components[i] == &target) continue;
        invalid[i] = 1;
      }
    }
  }
  for(int i = 0; i < invalid.size(); i++) {
    if(invalid[i] == 0) return true;
  }
  return false;
}

void Solver::solve() {
  
}
