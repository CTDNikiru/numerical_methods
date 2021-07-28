#pragma once
class Point
{
public:
	//конструктор
	Point(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}
	double x()const { return X; };
	double y()const { return Y; };
	double z()const { return Z; };

private:
	//координаты
	double X, Y, Z;
};