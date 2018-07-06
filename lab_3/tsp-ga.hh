
#include <vector>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include "Point.hh"
#include <cstdlib>
#include <ctime>
using namespace std;

class TSPGenome {

private:
  double length;
  vector<int> order;

public:
  // Constructors
  TSPGenome(int numPoints);                      // default constructor
  TSPGenome(const vector<int> &my_order);

  // Destructor
  ~TSPGenome();

  void computeCircuitLength(const vector<Point> &points);
  vector<int> getOrder() const;
  double getCircuitLength() const;
  void mutate();

};


TSPGenome findAShortPath(const vector<Point> &points, int populationSize, 
  int numGenerations, int keepPopulation, int numMutations);

bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);