#include "Gauss.h"
#include <iostream>
#include "Point.h"

Gauss::Gauss(int mode, double h, std::vector<Point> points, double (*function)(double)) {

	_points = points;
	func = function;
	_h = h;

	switch (mode)
	{
	case 1:
		ksi = { 0 };
		ai = { 2 };
		break;
	case 2:
		ksi = { 1.0 / sqrt(3.0), -1.0 / sqrt(3.0) };
		ai = { 1, 1 };
		break;
	case 3:
		ksi = { 0, sqrt(3.0/5.0), -sqrt(3.0/5.0) };
		ai = { 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0 };
		break;

	default:
		std::cout << "incorrect scheme";
		break;
	}
}

double Gauss::Integral() {
	/*
	double result = 0;

	
	double hk; //текущая длина сегмента
	double xi;

	for (int k = 1; k < _points.size(); k++) {

		hk = _points[k].x() - _points[k - 1].x();

		for (int i = 0; i < ai.size(); i++) {
			xi = ((hk * (ksi[i] + 1)) / 2) + _points[k - 1].x();
			result += ai[i] * func(xi);
		}

		result *= hk;

	}



	return result * 0.5;
	*/

	//результат (квадратурная сумма)
	double Result = 0.0;
	//начальная точка сегмента
	double X0;
	//шаг на отрезке
	double h = _h;
	//сумма по всем сегментам разбиения
	for (int i = 0; i < _points.size()-1; i++)
	{
		//начальная точка сегмента
		X0 = _points[0].x() + i * h;
		//сумма по узлам интегрирования
		for (int Integ_Point = 0; Integ_Point < ksi.size(); Integ_Point++)
		{
			//переход с мастер-элемента [-1, 1]
			auto P = Point(X0 + (1 + ksi[Integ_Point]) * h / 2.0, 0, 0);
			Result += ai[Integ_Point] * func(P.x());
		}
	}
	//формируем результат с учётом якобиана на отрезке [-1, 1]
	return Result * (h / 2.0);
}

double Gauss::error(double(*deriv)(double)) {
	double result = 0;

	double hk; //текущая длина сегмента

	for (int k = 1; k < _points.size(); k++) {
		hk = _points[k].x() - _points[k - 1].x();

		result += (pow(hk, (2 * ai.size()) + 1.0) * pow(factorial(ai.size()), 4)) * deriv(_points[k].x() - (hk / 2)) / (pow(factorial(2.0 * ai.size()), 3) * (2 * ai.size() + 1.0));
	
	}

	
	return result;

}

//факториал
int Gauss::factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}