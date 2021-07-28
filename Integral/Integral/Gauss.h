#pragma once
#include "Point.h"
#include <vector>

class Gauss
{
/*
��� ������ ��������� �������� �����
������� ������ ����� 1-5 � 2 ����������, ������������� ����� ������� ��� ����� �������������� �������� �������
� ��� ���������� ����� ����� ��������, � ��������� ����������� ������������ switch � ������������
*/

public:
	Gauss(int mode, double h, std::vector<Point> points, double (*function)(double));

	double Integral();
	double error(double(*deriv)(double));
	int factorial(int i);


private:
	std::vector <double> ksi; //����
	std::vector <double> ai; //����
	double _h;
	std::vector<Point> _points;
	double (*func)(double);
};

