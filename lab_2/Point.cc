#include "Point.hh"
#include <cmath>


// Default constructor:  initializes the point to (0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}

// Accessors:

double Point::getX() const{
  return x_coord;
}

double Point::getY() const{
  return y_coord;
}

double Point::getZ() const{
  return z_coord;
}

//New Member functions: 

//Returns a double that approximates the distance between the two points

double Point::distanceTo(const Point &p){
	return sqrt((x_coord - p.getX()) * (x_coord - p.getX()) + 
		(y_coord - p.getY()) * (y_coord - p.getY()) + 
    (z_coord - p.getZ()) * (z_coord - p.getZ()));

}
