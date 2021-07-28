#pragma once
#include "Point.h"
#include <vector>
class Newton
{
public:
	Newton(std::vector<Point> points, double (*function)(double), double h);
	double Integral();
	double error(double(*deriv)(double));
	int factorial(int i);

private:
	std::vector<Point> _points;
	double (*func)(double);
	double _h = 1;
};

