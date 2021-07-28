#pragma once
#include <vector>
#include "point.h"

class interpolation_cube
{

public:
	void Update_Spline(const std::vector<Point>& Points) {
		//обновление списка точек сплайна
		this->Points.clear();
		for (auto& elem : Points) this->Points.push_back(elem);

		//число отрезков разбиения
		int Num_Segment = Points.size() - 1;

		//длина текущего отрезка и следующего
		double h_current, h_next;

		//изменение размеров векторов коэффициентов
		a.resize(Num_Segment);
		b.resize(Num_Segment);
		c.resize(Num_Segment);
		d.resize(Num_Segment);

		//вектор правой части СЛАУ
		std::vector<double> f(Num_Segment - 1);

		//вычисление коэффициентов
		for (int i = 0; i < Num_Segment - 1; i++)
		{
			//длина текущего и следующего отрезков
			h_current = Points[i + 1].x() - Points[i].x();
			h_next = Points[i + 2].x() - Points[i + 1].x();

			//формируем диагональ
			b[i] = 2 * (h_current + h_next);
			//формируем нижнюю диагональ
			a[i + 1] = h_current;
			//формируем верхнюю диагональ
			d[i] = h_next;
			//правая часть
			f[i] = 3.0 * ((Points[i + 2].y() - Points[i + 1].y()) / h_next - (Points[i + 1].y() - Points[i].y()) / h_current);
		}

		//метод прогонки: прямой ход
		for (int j = 1; j < Num_Segment - 1; j++)
		{
			b[j] -= a[j] / b[j - 1] * d[j - 1]; //диагональ
			f[j] -= a[j] / b[j - 1] * f[j - 1]; //правая часть
		}

		//метод прогонки: обратный ход
		c[Num_Segment - 1] = f[Num_Segment - 2] / b[Num_Segment - 2];
		for (int j = Num_Segment - 2; j > 0; j--)
		{
			c[j] = (f[j - 1] - c[j + 1] * d[j - 1]) / b[j - 1];
		}

		//добавляем краевые условия нулевой кривизны
		c[0] = 0.0;

		for (int i = 0; i < Num_Segment - 1; i++)
		{
			h_current = Points[i + 1].x() - Points[i].x();
			a[i] = Points[i].y();
			b[i] = (Points[i + 1].y() - Points[i].y()) / h_current - (c[i + 1] + 2.0 * c[i]) * h_current / 3.0;
			d[i] = (c[i + 1] - c[i]) / h_current / 3.0;
		}

		//на последнем сегменте
		h_current = Points[Num_Segment].x() - Points[Num_Segment - 1].x();
		a[Num_Segment - 1] = Points[Num_Segment - 1].y();
		b[Num_Segment - 1] = (Points[Num_Segment].y() - Points[Num_Segment - 1].y()) / h_current - 2.0 * c[Num_Segment - 1] * h_current / 3.0;
		d[Num_Segment - 1] = -c[Num_Segment - 1] / h_current / 3.0;
	}

	//значение сплайна в точке
	double Spline_Value(const Point& P)const {
		double eps = 1e-7;
		int Num_Segment = Points.size() - 1;
		for (int i = 0; i < Num_Segment; i++)
		{
			if (P.x() > Points[i].x() && P.x() < Points[i + 1].x() || fabs(P.x() - Points[i].x()) < eps || fabs(P.x() - Points[i + 1].x()) < eps){
				double diff = (P.x() - Points[i].x());
				
				return (a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * pow(diff, 3));
			}
		}
		throw std::exception("The point is not found in the segments...");
	}

	//значение 1 производной сплайна в точке
	double Spline_deriv_Value(const Point& P)const {
		double eps = 1e-7;
		int Num_Segment = Points.size() - 1;
		for (int i = 0; i < Num_Segment; i++)
		{
			if (P.x() > Points[i].x() && P.x() < Points[i + 1].x() || fabs(P.x() - Points[i].x()) < eps || fabs(P.x() - Points[i + 1].x()) < eps) {
				double diff = (P.x() - Points[i].x());
				return (b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * pow(diff, 2));
			}
		}
		throw std::exception("The point is not found in the segments...");
	}

	//значение 2 производной сплайна в точке
	double Spline_deriv2_Value(const Point& P)const {
		double eps = 1e-7;
		int Num_Segment = Points.size() - 1;
		for (int i = 0; i < Num_Segment; i++)
		{
			if (P.x() > Points[i].x() && P.x() < Points[i + 1].x() || fabs(P.x() - Points[i].x()) < eps || fabs(P.x() - Points[i + 1].x()) < eps) {
				double diff = (P.x() - Points[i].x());
				return (2.0 * c[i] + 6.0 * d[i] * diff);
				
			}
		}
		throw std::exception("The point is not found in the segments...");
	}

	//Debug
	std::vector<double> A()const { return a; };
	std::vector<double> B()const { return b; };
	std::vector<double> C()const { return c; };
	std::vector<double> D()const { return d; };

private:
	//точки сетки
	std::vector<Point> Points;
	//коэффициенты сплайна
	std::vector<double> a, b, c, d;
};