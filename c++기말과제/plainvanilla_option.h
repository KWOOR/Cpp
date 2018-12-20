#pragma once
#include "option.h"

class PlainVanillaOption : public Option {
public:	
	PlainVanillaOption(Date expiration, double strike, OptionType type) : 
		Option(expiration, strike, type) {}
	double price();
	virtual double delta();
	virtual double gamma();
	virtual double vega();
	virtual double rho();
	virtual double theta();
	double impliedVol(double mktPrice);
	virtual double price_change(double ds = 0, double dvol = 0, double dr = 0);
	virtual double impliedVol_bisection(double mktPrice);
private:
	void setVolatility(double sigma) { 
		sigma_ = sigma; 
	}
};