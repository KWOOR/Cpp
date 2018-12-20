
#include "exam.h"
#include <iostream>
#include <string>
#include <vector>

#define SEPARATION() std::cout<<std::string(30,'-')<<std::endl

void printCoupon(Coupon& c) {
	for (int i = 0; i < 5; i++) {
		double index = 0.01 + 0.01*i;
		std::cout << "Coupon Amount (index " << index << ") = " 
			<< c.couponAmount(index) << std::endl;
	}
};

int main() {

	//Problem 1
	unsigned int n = 3;
    howManyMultiples(n);
	SEPARATION();

	////Problem 2
	int waitingCustomer = 5;
	int waitingMin = 6;
	double prob = waitingTime(waitingCustomer, waitingMin);
	std::cout << "Probability = " << prob << std::endl;
	SEPARATION();

	////Problem 3
	Pension ps(100, 30);
	for (int i = 0; i < 5; ++i) {
		double rate = 0.01 + i*0.01;
		std::cout << "Amount (" << rate << ") = " 
			<< ps.calcAmount(rate) << std::endl;
	}
	SEPARATION();

	////Problem 4
	std::vector<double> price = { 20, 23, 25, 30, 22, 15, 12, 21, 26, 20 };
	std::vector<int> num = { 30, 4, 6, 2, 5, 10, 7, 14, 8, 2 };
	std::vector<Position> pos = { Buy, Buy, Sell, Sell, Buy, Sell, Sell, Buy, Sell, Sell };
	std::vector<Trade> trades;
	for (int i = 0; i < price.size(); ++i)
		trades.push_back(Trade(price[i], num[i], pos[i]));
	std::vector<double> res = tradingAnalysis(trades);
	std::cout << "remaining position = " << res[0] << std::endl;
	std::cout << "avg. buy price = " << res[1] << std::endl;
	std::cout << "avg. sell price = " << res[2] << std::endl;
	SEPARATION();

	////Problem 5
	FixedCoupon fixed(10000, Quarterly, 0.04);
	FloatingCoupon floating(10000, Monthly, 0.001);
	std::cout << "Fixed Coupon:" << std::endl;
	printCoupon(fixed);
	std::cout << "Floating Coupon:" << std::endl;
	printCoupon(floating);

	return 0;
}