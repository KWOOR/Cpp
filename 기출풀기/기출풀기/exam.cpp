#define _USE_MATH_DEFINES
#include "exam.h"
#include <iostream>
#include <cmath>
#include <random>
#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)>(y))?(x):(y))


void howManyMultiples(unsigned int n)
{
	int input1;
	std::cin >> input1;
	int input2;
	std::cin >> input2;
	std::cout << "input1=" << input1 << std::endl;
	std::cout << "input2=" << input2 << std::endl;
	int number = 0;
	for (int i = MIN(input1, input2) ; i <= MAX(input1, input2); i++)
	{
		if (i%n==0)
		{
			number += 1;
		}
	}
	std::cout << "Number of multiples of " << n << " is " << number << std::endl;
}


double waitingTime(int n, int m)
{
	std::mt19937_64 gen;
	std::normal_distribution<double> dist(0.0, 1.0);
	
	double simnum = 10000.0;
	double count = 0.0;
	for (int i = 0; i < simnum; i++)
	{
		double time = 0;
		for (int i = 0; i < n; i++)
		{
			double x = dist(gen);
			time += exp(x);
		}
		
		if (time<=m)
		{
			count += 1;
		}
	}
	return count/simnum;
}

std::vector<double> tradingAnalysis(std::vector<Trade> trades)
{
	std::vector<double> buff;
	double numbuy = 0;
	double numsell = 0;
	double num = 0;
	double numbuyprice = 0;
	double numsellprice = 0;
	for (int i = 0; i < trades.size(); i++)
	{
		num += trades[i].numOFShares_ *trades[i].position_;
		if (trades[i].position_==1)
		{
			numbuyprice+= ((trades[i].numOFShares_) *(trades[i].price_));
			numbuy += trades[i].numOFShares_;
		}
		else
		{
			numsellprice+= ((trades[i].numOFShares_) *(trades[i].price_));
			numsell += trades[i].numOFShares_;
		}
	}
	buff.push_back(num);
	buff.push_back(numbuyprice / numbuy);
	buff.push_back(numsellprice / numsell);

	return buff;
}

double Pension::calcAmount(double r)
{
	double money = 0.0;
	for (int i = 0; i < n_; i++)
	{
		money+= (1 / (pow((1 + r), (i + 1))));
	}
	return a_/money;
}


double FixedCoupon::couponAmount(double libor)
{
	double c = (principal_*fixedRate_ )/ (freq_);
	return c;
}

double FloatingCoupon::couponAmount(double libor)
{
	double c = (principal_*(libor + spread_)) / (freq_);
	return c;
}
