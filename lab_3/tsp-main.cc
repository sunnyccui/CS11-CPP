#include "tsp-ga.hh"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void usage(const char *progname) {
	cout << "usage: " << progname << " population generations keep mutate" << endl;
	cout << "\tpopulation is a positive integer" << endl;
	cout << "\tgenerations is a positive integer" << endl;
	cout << "\tkeep is a nonnegative float" << endl;
	cout << "\tmutate is a nonnegative float" << endl;
}

int main(int argc, char **argv){

	if (argc != 5){
		usage(argv[0]);
			return 1;
	}

	int population = (int) atoi(argv[1]);
	int generations = (int) atoi(argv[2]);;
	float keep = (float) atof(argv[3]);
	int keepPopulation = keep * population;
	double mutate = (float) atof(argv[4]);
	int mutations = mutate * population;


	cout << "How many points?" << endl;
	int num_points;
	cin >> num_points;

	vector <Point> my_points;

	for (int i =0; i < num_points; i++){
		float x, y, z;
		cin >> x >> y >> z;
		Point p1(x, y, z);
		my_points.push_back(p1);
	}

	srand(time(nullptr));

	TSPGenome best_order = findAShortPath(my_points, population, 
		generations, keepPopulation, mutations);
	vector<int> my_order = best_order.getOrder();
	cout << "Best order: [";
	for (int i = 0; i  < my_order.size(); i++){
		cout << my_order[i] << " ";
	}
	cout << "]" << endl;
	double distance = best_order.getCircuitLength();
	cout << "Shortest distance:  " << distance << endl;

	return 0;
}