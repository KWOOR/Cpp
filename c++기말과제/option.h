#pragma once

#include "date.h"
#include "gbmprocess.h"
enum OptionType { Call = 1, Put = -1 };

class Option {  // �ƹ��� ����� ���� - �ڽ�Ŭ���� ������ ����и� ���� -> �߻�(Abstract) Ŭ���� : pure virtual�Լ��� ������ �ִ� �Լ� - �θ�class�� ������ �� ����.
public:
	Option(Date expiration, double strike, OptionType type) :
		expiration_(expiration), strike_(strike), type_(type) {}
	void setProcess(GBMProcess p, Date d);
	void setEvalDate(Date d);
	void changedata(double ds = 0, double dvol = 0, double dr = 0);
	virtual double price_change(double ds = 0, double dvol = 0, double dr = 0) { return 0; };
	virtual double price() = 0; // pure virtual�Լ� : =0�� ���̸� �Լ��� �������� �ʾƵ� �ȴ�. ( �ڽ� class������ �ʿ��� �Լ��μ� �ڽ�class������ �ݵ�� overriding�ؾ� ��. ������ virtual�� ������ �־�� ��)
	virtual double delta();
	virtual double gamma();
	virtual double vega(); // �߻�(Abstract) Ŭ���� : pure virtual�Լ��� ������ �ִ� �Լ� - �θ�class�� ������ �� ����.
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


