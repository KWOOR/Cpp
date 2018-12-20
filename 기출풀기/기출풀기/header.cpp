#include "header.h"


double solveEquation(double x[3], double y[3], double value[2])
{

	if (((x[0] * y[1]) - (x[1] * y[0])) == 0 &&((x[0]/y[0]) == (x[2]/y[2])))
		return 2;

	else if (((x[0] * y[1]) - (x[1] * y[0])) == 0 && ((x[0] / y[0]) != (x[2] / y[2])))
	{
		return 1;
	}
	else
	{
		value[0] = ((y[1] * x[2]) - (x[1] * y[2])) / ((x[0] * y[1]) - (x[1] * y[0]));
		value[1] = ((x[0] * y[2]) - (y[0] * x[2])) / ((x[0] * y[1]) - (x[1] * y[0]));
		return 0;
	}
}

double* OLS::params()
{
	double sumy = 0.0;
	for (int i = 0; i < y_.size(); i++)
	{
		sumy += y_[i];
	}

	double sumx = 0.0;
	for (int i = 0; i < x_.size(); i++)
	{
		sumx += x_[i];
	}
	double sumxsq = 0.0;
	for (int i = 0; i < x_.size(); i++)
	{
		sumxsq += pow(x_[i],2);
	}
	double sumxy = 0.0;
	for (int  i = 0; i < x_.size(); i++)
	{
		sumxy += (x_[i])*(y_[i]);
	}

	double b = ((x_.size()*sumxy) - (sumx*sumy)) / (x_.size()*sumxsq - (pow(sumx, 2)));

	double a = (sumy / x_.size()) - ((b*sumx)/(x_.size()));
	return &a,&b;
}
