#include "tsp-ga.hh"
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

TSPGenome::TSPGenome(int numPoints) {
  for (int i = 0; i < numPoints; i++){
    order.push_back(i);
  }
  random_shuffle(order.begin(), order.end());
  length = -1;
}


// Constructor initializes the genome from the specified visit order
TSPGenome::TSPGenome(const vector<int> &my_order){
  order = my_order;
  length = -1;
}


// Destructor - Point allocates no dynamic resources.
TSPGenome::~TSPGenome() {
  // no-op
}


// Returns the genome's current visit order
vector<int> TSPGenome::getOrder() const{
  return order;
}

// Takes a const-reference to a vector of points, and computes the circuit length 
// from traversing the points in the order specified in the object
void TSPGenome::computeCircuitLength(const vector<Point> &points){
  double sum = 0.0;
  if (order.size() >= 1){
    for (int i =0; i < order.size() -1; i++){
      Point p1 = points[order[i]];
      Point p2 = points[order[i+1]];
      sum += p1.distanceTo(p2);
    }
  }
  Point p1 = points[order.front()];
  Point p2 = points[order.back()];
  sum += p2.distanceTo(p1);
  length = sum;
}

// Returns the circuit length
double TSPGenome::getCircuitLength() const{
  return length;
}

// Mutates the genome by swapping two randomly-selected values in the order vector
void TSPGenome::mutate(){
  int i_1 = rand() % order.size();
  int i_2 = rand() % order.size();
  while (i_1 == i_2){
    i_2 = rand() % order.size();
  }
  int temp = order[i_1];
  order[i_1] = order[i_2];
  order[i_2] = temp;
}


bool isGenomeValid(const vector<int> &order) {
  set<int> s;
  for (int i = 0; i < order.size(); i++) {
    if (s.count(i) != 0) {
      cout << "Error: value " << i << " is repeated!" << endl;
      return false;
    }
    s.insert(i);
  }
  return true;
}


TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2){
  vector<int> order_1 = g1.getOrder();
  int i = rand() % order_1.size();
  vector<int> sub(order_1.begin(), order_1.begin() + i);
  set<int> s;
  s.insert(sub.begin(), sub.end());
  vector<int> order_2 = g2.getOrder();
  for (int i =0; i < order_2.size(); i++){
      if (s.count(order_2[i]) == 0){
        sub.push_back(order_2[i]);
        s.insert(order_2[i]);
      }
  }
  TSPGenome new_genome(sub);
  return new_genome;
}


bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2){
  double s1 = g1.getCircuitLength();
  double s2 = g2.getCircuitLength();
  return s1 < s2;
}


TSPGenome findAShortPath(const vector<Point> &points, int populationSize, 
  int numGenerations, int keepPopulation, int numMutations){

  // gen is the generation #; it starts at 0
  // population is the vector of TSP genomes
  vector<TSPGenome> population;
  for (int i =0; i < populationSize; i++){
    TSPGenome gen(points.size());
    gen.computeCircuitLength(points);
    population.push_back(gen);
  }

  for (int i =0; i < numGenerations; i++){
    for (int i =0; i < populationSize; i++){
      population[i].computeCircuitLength(points);
    }
    
    sort(population.begin(), population.end(), isShorterPath);

    for (int i =0; i < populationSize; i++){
      population[i].computeCircuitLength(points);
    }


    if (i % 10 == 0) {
        cout << "Generation " << i << ":  shortest path is ";
        cout << population[0].getCircuitLength() << endl;
    }

    for (int i = keepPopulation; i < populationSize; i++){
      int g1 = rand() % keepPopulation;
      int g2 = rand() % keepPopulation;
      while (g1 == g2){
        g2 = rand() % keepPopulation;
      }
      population[i] = crosslink(population[g1], population[g2]);
    }

    // Mutate
    for (int i =0; i < numMutations; i++){
      int j = 1 + rand() % (populationSize - 1);
      population[j].mutate();
    }
  }

  return population[0];
}

