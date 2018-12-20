#pragma once

#include "date.h"
#include "gbmprocess.h"
enum OptionType { Call = 1, Put = -1 };

class Option {  // 아무런 기능은 없음 - 자식클래스 구현의 공통분모 모음 -> 추상(Abstract) 클래스 : pure virtual함수를 가지고 있는 함수 - 부모class는 정의할 수 없다.
public:
	Option(Date expiration, double strike, OptionType type) :
		expiration_(expiration), strike_(strike), type_(type) {}
	void setProcess(GBMProcess p, Date d);
	void setEvalDate(Date d);
	void changedata(double ds = 0, double dvol = 0, double dr = 0);
	virtual double price_change(double ds = 0, double dvol = 0, double dr = 0) { return 0; };
	virtual double price() = 0; // pure virtual함수 : =0을 붙이면 함수를 정의하지 않아도 된다. ( 자식 class에서만 필요한 함수로서 자식class에서는 반드시 overriding해야 함. 때문에 virtual이 무조건 있어야 함)
	virtual double delta();
	virtual double gamma();
	virtual double vega(); // 추상(Abstract) 클래스 : pure virtual함수를 가지고 있는 함수 - 부모class는 정의할 수 없다.
	virtual double rho();
	virtual double theta();
	virtual double impliedVol(double m) { return 10; }
	virtual double impliedVol_bisection(double mktPrice) { return 10; }
	double s_, r_, q_, t_, sigma_;
protected:
	double getd1();
	double getd2();

	Date evalDate_;
	Date expiration_;
	double strike_;
	OptionType type_;
	GBMProcess p_;

};


