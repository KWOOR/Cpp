#define _USE_MATH_DEFINES
#include <cmath>
#pragma once


double firstPassTime(double mu, double sigma, double b, unsigned int ns);
double bondprice(double couponRate, double yield, int T, int n);
double duration(double couponRate, double yield, int T, int n);
double yield(double price, double couponRate, int T, int n);


class InterestRate {
public: InterestRate(double rate) :rate_(rate) {}
		virtual ~InterestRate() {}
		virtual double discount(double t) = 0;

protected: double rate_;
//private: double rate_;
};

enum Frequency {Annual=1, Semiannual=2, Quarterly=4};
class CompoundedRate :public InterestRate {
public: CompoundedRate(double rate, Frequency n) :InterestRate(rate), n_(n){}
		double discount(double t);

private: Frequency n_;
};

class ContinuousRate : public InterestRate {
public: ContinuousRate(double rate) : InterestRate(rate){}
		double discount(double t);
};

class Password {
public: Password(int n) : n_(n) { password_ = new int[n_]; }
		~Password() { delete[] password_; }
		void printPassword();
private: int n_;
		 int* password_;
};