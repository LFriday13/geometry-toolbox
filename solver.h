#include "GeoComponents.h"
#include "PointNode.h"
#include "LineNode.h"
#include "CircleNode.h"
#include "TriangleNode.h"
#include "TriangleCentersNode.h"

class Solver {
public:
  Solver(GeoComponents*, GeoNode*);
  bool check();
  void solve();
private:
  GeoComponents main_data;
  GeoNode* target;
  const int check_trial_time = 20;
};
