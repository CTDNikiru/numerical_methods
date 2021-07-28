#pragma once
#include "Point.h"
#include <vector>

class Rect
{
public:
	Rect(std::vector<Point> points, double (*function)(double));
	double Integral();
	double error(double(*deriv)(double));
	int factorial(int i);

private:
	std::vector<Point> _points;
	double (*func)(double);
};

