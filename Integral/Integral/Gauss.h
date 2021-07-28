#pragma once
#include "Point.h"
#include <vector>

class Gauss
{
/*
Для начала определим основной класс
отличия формул Гаусс 1-5 в 2 переменных, следовательно нужно сделать так чтобы использовались основные формулы
а две переменные можно легко заменить, в частности предполагаю использовать switch в конструкторе
*/

public:
	Gauss(int mode, double h, std::vector<Point> points, double (*function)(double));

	double Integral();
	double error(double(*deriv)(double));
	int factorial(int i);


private:
	std::vector <double> ksi; //узлы
	std::vector <double> ai; //веса
	double _h;
	std::vector<Point> _points;
	double (*func)(double);
};

