#include "Point.h"

Point::Point(double x, double y, double z){
	_x = x;
	_y = y;
	_z = z;
}

double Point::x() {
	return _x;
}

double Point::y() {
	return _y;
}

double Point::z() {
	return _z;
}