#pragma once
#include <valarray>

double solveEquation(double x[3], double y[3], double value[2]);

class OLS {
public: OLS(std::valarray<double> x, std::valarray<double> y): x_(x), y_(y){ }
		~OLS() {}
		double* params();

private: std::valarray<double> x_;
		 std::valarray<double> y_;

};


