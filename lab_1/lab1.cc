#include "Point.hh"
#include <cmath>
#include <iostream>
#include <cstdio>
using namespace std;

// takes by reference three Point objects
// computes the area within the triangle defined by these points using Heron's Formula
// returns it as a double-precision floating point number.
double computeArea(Point &a, Point &b, Point &c){
	double l1 = a.distanceTo(b);
	double l2 = a.distanceTo(c);
	double l3 = b.distanceTo(c);
	double s = (l1 + l2 + l3) / 2;
	return sqrt(s * (s - l1) * (s - l2) * (s - l3));
}

int main(){
	float x, y, z;
	cout << "Enter x, y and z coordinates of Point #1: ";
	cin >> x >> y >> z;
	Point p1(x, y, z);

	cout << "Enter x, y and z coordinates of Point #2: ";
	cin >> x >> y >> z;
	Point p2(x, y, z);

	cout << "Enter x, y and z coordinates of Point #1: ";
	cin >> x >> y >> z;
	Point p3(x, y, z);

	double area = computeArea(p1, p2, p3);

	cout <<   "Point 1:  <" << p1.getX() << p1.getY() << p1.getZ() << ">" << endl;
	cout <<   "Point 2:  <" << p2.getX() << p2.getY() << p2.getZ() << ">" << endl;
	cout <<   "Point 3:  <" << p3.getX() << p3.getY() << p3.getZ() << ">" << endl;
	cout << "Area is:  <" << area << " >";

	return 0;

}