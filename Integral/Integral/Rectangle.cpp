#include "Rectangle.h"

Rect::Rect(std::vector<Point> points, double(*function)(double)) {
	_points = points;
	func = function;
}

double Rect::Integral() {
	double result = 0;
	double h = 0;

	for (int i = 1; i < _points.size(); i++) {
		h = _points[i].x() - _points[i - 1].x();

		double xi = (_points[i].x() + _points[i - 1].x()) / 2;
		double y = func(xi);

		result += h*y;

		//добавить погрешность апроксимации
	}

	return result;
}

double Rect::error(double(*deriv)(double)) {
	double result = 0;

	double hk; //текущая длина сегмента

	for (int k = 1; k < _points.size(); k++) {
		hk = _points[k].x() - _points[k - 1].x();

		result += (pow(hk, 3.0) * deriv(_points[k].x() - (hk / 2)) / 24.0);

	}


	return result;

}
//факториал
int Rect::factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}