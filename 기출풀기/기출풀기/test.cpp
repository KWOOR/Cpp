#include "test.h"
#include <random>
#include <iostream>

double firstPassTime(double mu, double sigma, double b, unsigned int ns)
{
	std::mt19937_64 gen;
	std::normal_distribution<double> dist(mu, sigma);
	//gen.seed(std::random_device{}());
	double n = 0;
	for (int i= 0;  i <ns; ++i)
	{
		int month = 1;
		double price = 100;
		while (price > b )
		{
			double x = dist(gen);
			price = price * (1.0 + x);
			if (price>b)
			{
				month += 1;
			}
		}
		n += month;
	}
	return n/ns;
}	

double bondprice(double couponRate, double yield, int T, int n)
{
	double coupon = 0;
	for (int i = 1; i <= n*T; i++)
	{
		coupon += (couponRate/n) * exp(-yield * (i/n));
	}
	double bond = exp(-yield * T);
	return coupon+bond;
}

double duration(double couponRate, double yield, int T, int n)
{
	double Price = bondprice(couponRate, yield, T, n);
	double coupon = 0;
	for (int i = 1; i <= n * T; i++)
	{
		coupon += (i/n)*(couponRate / n) * exp(-yield * (i / n));
	}
	double bond = T*exp(-yield * T);
	return (coupon+bond)/Price;
}

double yield(double price, double couponRate, int T, int n)
{
	double e = 100; 
	double ytm = 0.05;
	double tol = 1e-8;
	while (abs(e) > tol)
	{
		double Price = bondprice(couponRate, ytm, T, n);
		e = price - Price ;
		ytm = ytm - e/ (Price*duration(couponRate, ytm, T,n));
	}
	return ytm;
}

double CompoundedRate::discount(double t)
{
	return pow((1+rate_/n_),(-n_*t));
}

double ContinuousRate::discount(double t)
{
	return exp(-rate_*t);
}

void Password::printPassword()
{
	for (int i = 0; i < n_; i++)
	{
		password_[i] = rand()%10;
		std::cout << password_[i];
	}
	std::cout<< "\t" <<std::endl;
}
