#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <ctime>
#include <random>
#include <cmath>

enum WeekDay
{Wed=0, Thu=1, Fri=2, Sat=3, Sun=4, Mon=5, Tue=6};

WeekDay weekday(int year, int month, int day);

std::vector<double> distance(int n);

double worstReturn(double sigma1, double sigma2, double rho, int n=10000);

class NormalDist {
public: NormalDist(double mu, double sigma) : mu_(mu), sigma_(sigma) {}
		~NormalDist() {}
		double cdf(double x);
		double invcdf(double prob);

private: double mu_;
		 double sigma_;
};

class DataBill {
public: DataBill(double base) :base_(base) {}
		virtual ~DataBill() {}
		virtual double billingAmt(double usage) = 0;
		bool compareWith(DataBill* plans, double usages);
protected: double base_;
};
class PlanA :public DataBill{
public: PlanA(double base, double unitCharge) : DataBill(base), unitCharge_(unitCharge) {}
		double billingAmt(double usage);
private: double unitCharge_;
};

class PlanB :public DataBill {
public: PlanB(double base, std::vector<double> sections, std::vector<double> additionalCharges) : DataBill(base), sections_(sections), additionalCharges_(additionalCharges) {}
		double billingAmt(double usage);

private: std::vector<double> sections_;
		 std::vector<double> additionalCharges_;
};