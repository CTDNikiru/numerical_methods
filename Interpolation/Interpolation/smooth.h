#pragma once
#include "cubic.h"

class smooth {
public:
	smooth(const double& SMOOTH) {  this->SMOOTH = SMOOTH; };

	void update_smooth(std::vector<Point> &Points) {
		this->points.clear();
		for (int i = 0; i < Points.size(); i++) {
			points.push_back(Points[i]);
		}
		int Num_segments = Points.size() - 1;

		alpha.resize(Num_segments + 1);

		std::vector<double> a, b, c;
		a.resize(Num_segments + 1); b.resize(Num_segments + 1); c.resize(Num_segments + 1);

		for (int i = 0; i < Num_segments; i++) {
			double W = 1.0;
			//here is a trouble
			Assembling(i, this->points[i], points[i].y(), W, a, b, c);
			Assembling(i, this->points[i + 1], points[i + 1].y(), W, a, b, c);

			double h = Points[i + 1].x() - Points[i].x();
			b[i] += 1.0 / h * SMOOTH;
			b[i+1] += 1.0 / h * SMOOTH;
			a[i+1] -= 1.0 / h * SMOOTH;
			c[i] -= 1.0 / h * SMOOTH;

		}

		for (int j = 1; j < Num_segments + 1; j++) {
			b[j] -= a[j] / b[j - 1] * c[j - 1];
			alpha[j] -= a[j] / b[j - 1] * alpha[j - 1];
		}

		alpha[Num_segments] /= b[Num_segments];
		for (int j = Num_segments - 1; j >= 0; j--)
			alpha[j] = (alpha[j] - alpha[j + 1] * c[j]) / b[j];

	}

	void Get_Value(const Point& P, double* Res) const {
		double eps = 1e-7;

		int Num_Segments = points.size() - 1;
		double X = P.x();

		for (int i = 0; i < Num_Segments; i++) {
			if (X > points[i].x() && X < points[i + 1].x() || fabs(X - points[i].x()) < eps || fabs(X - points[i + 1].x()) < eps) {
				double h = points[i + 1].x() - points[i].x();
				double Ksi;
				Translation_To_Master_Element(i, X, Ksi);

				Res[0] = alpha[i] * Basis_Function(1, Ksi) + alpha[i + 1] * Basis_Function(2, Ksi);
				Res[1] = (alpha[i] * Der_Basis_Function(1, Ksi) + alpha[i + 1] * Der_Basis_Function(2, Ksi)) * 2.0 / h;
				Res[2] = 0;
				return;
			}
		}
		throw std::exception("The point is not found");
			 
	}


private:
	double SMOOTH;
	std::vector<Point> points;
	std::vector<double> alpha;

	void Translation_To_Master_Element(int Seg_Num, const double& X, double& Ksi) const {
		Ksi = 2.0 * (X - points[Seg_Num].x()) / (points[Seg_Num + 1].x() - points[Seg_Num].x()) - 1.0;
	}

	double Basis_Function(int Number, const double& Ksi) const {
		switch (Number)
		{
		case 1:
			return (0.5 * (1 - Ksi));
			break;
		case 2:
			return (0.5 * (1 + Ksi));
			break;
		default:
			throw std::exception("Error in basis_function");
			break;
		}
	}

	double Der_Basis_Function(int Number, const double& Ksi) const {
		switch (Number)
		{
		case 1:
			return -0.5;
			break;
		case 2:
			return 0.5;
			break;
		default:
			throw std::exception("Error in der_basis_function");
			break;
		}
	}

	void Assembling(int i, const Point& P, const double& F_Val, const double& w, std::vector<double>& a, std::vector<double>& b, std::vector<double>& c) {
		double X = P.x(), Ksi;
		Translation_To_Master_Element(i, X, Ksi);
		double f1 = Basis_Function(1, Ksi);
		double f2 = Basis_Function(2, Ksi);

		b[i] += (1.0 - SMOOTH) * w * f1 * f1;
		b[i + 1] += (1.0 - SMOOTH) * w * f2 * f2;
		a[i + 1] += (1.0 - SMOOTH) * w * f1 * f2;
		c[i] += (1.0 - SMOOTH) * w * f2 * f1;

		alpha[i] += (1.0 - SMOOTH) * w * f1 * F_Val;
		alpha[i + 1] += (1.0 - SMOOTH) * w * f2 * F_Val;
	}
};