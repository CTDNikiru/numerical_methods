#include <iostream>
#include <vector>
#include <algorithm>
#include "cubic.h";
#include "point.h"
#include "smooth.h"
#include "split.h"



std::vector<Point> get_func(std::vector<Point> points) {
	std::vector<Point> _points;
	double function;
	for (int i = 0; i < points.size(); i++) {
		function = points[i].x() * abs(sin(10000* points[i].x()));
		_points.push_back(Point(points[i].x(), function, 0));
	}
	return _points;
}

double get_error(std::vector<Point> func, interpolation_cube cube) {

	std::vector<double> diff;

	for (int i = 0; i < func.size(); i++) {
		diff.push_back(abs(func[i].y() - cube.Spline_Value(func[i].x())));
	}

	double result = diff[0];

	for (int i = 1; i < diff.size(); i++) {
		if (result < diff[i]) {
			result = diff[i];
		}
	}

	return result;

}

//получение производной функции в точке
std::vector<Point> get_deriv(std::vector<Point> func) {
	std::vector<Point> result;
	for (int i = 0; i < func.size() - 1; i++) {
		result.push_back(Point(func[i].x(), ((func[i + 1].y() - func[i].y()) / (func[i + 1].x() - func[i].x()))));
	}
	return result;
}

//точность 1 производной
double get_deriv_error(std::vector<Point> func, interpolation_cube cube) {

	std::vector<double> diff;
	func = get_deriv(func);

	for (int i = 0; i < func.size(); i++) {
		diff.push_back(abs(func[i].y() - cube.Spline_deriv_Value(func[i].x())));
	}

	double result = diff[0];

	for (int i = 1; i < diff.size(); i++) {
		if (result < diff[i]) {
			result = diff[i];
		}
	}

	return result;

}

//точность 2 производной
double get_deriv2_error(std::vector<Point> func, interpolation_cube cube) {

	std::vector<double> diff;
	func = get_deriv(get_deriv(func)); // f''(x) = (f'(x))'

	for (int i = 0; i < func.size(); i++) {
		diff.push_back(abs(func[i].y() - cube.Spline_deriv2_Value(func[i].x())));
	}

	double result = diff[0];

	for (int i = 1; i < diff.size(); i++) {
		if (result < diff[i]) {
			result = diff[i];
		}
	}

	return result;

}



int main() {

	std::vector<Point> points = get_func(split::regular(0, 1, 0.05));
	smooth smooth_spline(0.5);
	smooth_spline.update_smooth(points);
	interpolation_cube cubic;
	cubic.Update_Spline(points);

	double* res = new double[3];

	for (int i = 0; i < points.size(); i++) {
		smooth_spline.Get_Value(points[i].x(), res);

		std::cout << "\t" << points[i].x() << "\t" << cubic.Spline_Value(points[i].x()) << "\t" << res[0] << "\n";
	}
}

