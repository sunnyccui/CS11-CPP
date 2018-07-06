#include "Point.hh"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

/*This function takes a vector of points, 
and the order in which those points are visited,
and it computes the total length of the path when 
the points are traveled in the specified order
*/ 

 double circuitLength(const vector<Point> &points, const vector<int> &order){
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
 	return sum;
 	
 }


/* This function takes a vector of points, 
and returns a vector that specifies the order to visit all of the points in a single round trip, 
visiting each point once, to ensure that the trip is as short as possible.
*/
vector<int> findShortestPath(const vector<Point> &points){
	vector <int> order;
	for (int i = 0; i < points.size(); i++){
		order.push_back(i);
	}
	vector <int> best_order = order;
	double path_size = circuitLength(points, order);
	do{
		double n = circuitLength(points, order);
		if (n < path_size){
			best_order = order;
			path_size = n;
		}
	} while (next_permutation(order.begin(), order.end()) );
	return best_order;

}


int main(){
	int num_points;
	cout << "How many points? ";
	cin >> num_points;
	vector <Point> my_points;

	for (int i =0; i < num_points; i++){
		float x, y, z;
		cin >> x >> y >> z;
		Point p1(x, y, z);
		my_points.push_back(p1);
	}

	for (int i =0; i < num_points; i++){
		cout <<   "Point " << i << ": " << my_points[i].getX() << " " <<
		my_points[i].getY() << " " << my_points[i].getZ() << endl; 
	}

	vector<int> best_order = findShortestPath(my_points);
	cout << "Best order:  [";
	for (int i =0; i < num_points; i++){
		cout << best_order[i] << " ";
	}
	cout << "]" << endl;
	cout << "Shortest distance:  " << circuitLength(my_points, best_order) << endl;

	return 0;

}