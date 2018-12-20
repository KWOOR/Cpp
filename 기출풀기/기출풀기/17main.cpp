#include <iostream>
#include <string>
#include "test.h"

int main() {
	// Problem 1
	double t = firstPassTime(0.001, 0.05, 95, 1000);
	std::cout << "expection = " << t << std::endl;
	std::cout << std::string(30, '-') << std::endl;

	// Problem 2
	double couponRate = 0.035;
	double y = 0.0215;
	int T = 5;
	int n = 2;
	double mktprice = 1.0;
	double price = bondprice(couponRate, y, T, n);
	double dur = duration(couponRate, y, T, n);
	double ytm = yield(mktprice, couponRate, T, n);
	std::cout << "price = " << price << std::endl;
	std::cout << "duration = " << dur << std::endl;
	std::cout << "yield = " << ytm << std::endl;
	std::cout << std::string(30, '-') << std::endl;

	// Problem 3
	CompoundedRate r1(0.04, Semiannual);
	ContinuousRate r2(0.04);  
	for (int i = 0; i < 10; ++i) {
		printf("%d : %0.5f  %0.5f\n",
			i, r1.discount(i), r2.discount(i));
	}
	std::cout << std::string(30, '-') << std::endl;

	//// Problem 4
	Password p(6);
	p.printPassword();
	std::cout << std::string(30, '-') << std::endl;
	std::cout << "Done!!" << std::endl;
	return 0;
}