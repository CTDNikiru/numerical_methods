#include "Newton.h"

Newton::Newton(std::vector<Point> points, double(*function)(double), double h) {
	_points = points;
	func = function;
	_h = h;
}

//распределение должно быть равномерным.
double Newton::Integral() {
	double result = 0;

	for (int i = 1; i < _points.size() - 1; i++) {
		result += func(_points[i].x());
	}

	result = (_h / 2)*(func(_points[0].x()) + 2*result + func(_points[_points.size()-1].x()));



	return result;
}

double Newton::error(double(*deriv)(double)) {
	double result = 0;

	double hk; //текущая длина сегмента


	for (int k = 1; k < _points.size(); k++) {
		hk = _points[k].x() - _points[k - 1].x();

		result += (pow(hk, 3.0) * deriv(_points[k].x() - (hk/2)) / 12.0);

	}


	return result;

}

//факториал
int Newton::factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}