#pragma once
class Point
{
public:
	Point(double x, double y, double z);

	double x();
	double y();
	double z();

private:
	double _x;
	double _y;
	double _z;
};

