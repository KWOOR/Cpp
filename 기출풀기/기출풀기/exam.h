#pragma once
#include <vector>

void howManyMultiples(unsigned int n);
double waitingTime(int n, int m);

class Pension {
public: Pension(double a, unsigned int n) : a_(a), n_(n) {}
		~Pension() {}
		double calcAmount(double r);
private: double a_;
		 unsigned int n_;
};

enum Position{Buy=1, Sell=-1};
class Trade {
public: Trade(double price, int numOFShares, Position position) : price_(price), numOFShares_(numOFShares), position_(position) {}
		~Trade() {}
		double price_;
		int numOFShares_;
		Position position_;

};
std::vector <double> tradingAnalysis(std::vector<Trade> trades);


enum Frequency { Monthly=12, Quarterly=4, Annually=1 };
class Coupon {
public: Coupon(double principal, Frequency freq) : principal_(principal), freq_(freq) {}
		virtual~Coupon() {}
		virtual double couponAmount(double libor) = 0;

protected: double principal_;
		   Frequency freq_;
};

class FixedCoupon :public Coupon{
public: FixedCoupon(double principal, Frequency freq, double fixedRate) :Coupon(principal, freq), fixedRate_(fixedRate) {}
		~FixedCoupon() {};
		double couponAmount(double libor);

private: double fixedRate_;
};

class FloatingCoupon : public Coupon {
public: FloatingCoupon(double principal, Frequency freq, double spread) : Coupon(principal, freq), spread_(spread) {}
		~FloatingCoupon() {};
		double couponAmount(double libor);

private: double spread_;
};
