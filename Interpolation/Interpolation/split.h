#pragma once
class split
{
#include <iostream>
#include <vector>
#include "point.h"

public:
	static std::vector<Point> regular(double start_point, double end_point, double step) {
		double temp = 0;
		std::vector<Point> points;
		while (temp < end_point + step) {
			points.push_back(temp);
			temp += step;
		}
		return points;
	}

	static std::vector<Point> adaptive(double start_point, double h, double r, double count) {
		if (r <= 1) {
			throw new std::exception;
		}

		std::vector<Point> result;

		for (int i = 0; i < count; i++) {
			result.push_back(start_point);
			start_point += h;
			h *= r;
		}

		return result;
	}
};