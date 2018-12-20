#include "test.h"


WeekDay weekday(int year, int month, int day)
{
	std::tm a = { 0,0,0, day, month - 1, year - 1900 };
	std::tm b = { 0,0,0, 17, 9, 118 };
	std::time_t x = std::mktime(&a);
	std::time_t y = std::mktime(&b);
	int difference = std::difftime(y, x) / (60 * 60 * 24);
	if (difference % 7 == 0)
		return Wed;
	else if (difference % 7 == 1 || difference % 7 == -6)
		return Thu;
	else if (difference % 7 == 2 || difference % 7 == -5)
		return Fri;
	else if (difference % 7 == 3 || difference % 7 == -4)
		return Sat;
	else if (difference % 7 == 4 || difference % 7 == -3)
		return Sun;
	else if (difference % 7 == 5 || difference % 7 == -2)
		return Mon;
	else
	{
		return Tue;
	}
}


std::vector<double> distance(int n)
{
	std::vector<double> empty;
	std::vector<double> dist;
	for (int num = 0; num < 10000; num++)
	{
		double right = 0.0;
		double left = 0.0;
		double up = 0.0;
		double down = 0.0;

		for (int i = 0; i < n; i++)
		{
			int a = rand();
			if ((a % 4) == 0)
				right += 1.0;
			else if ((a % 4) == 1)
				left -= 1.0;
			else if ((a % 4) == 2)
				up += 1.0;
			else
			{
				down -= 1.0;
			}
		}
		dist.push_back(sqrt((((right) + (left))*((right) + (left))) + ((((up) + (down))*((up) + (down))))));
	}

	double mu = 0.0;
	for (int i = 0; i < dist.size(); i++)
	{
		mu += dist[i];
	}

	mu/=10000;

	double sigma = 0.0;
	for (int i = 0; i < dist.size(); i++)
	{
		sigma += pow(((dist[i]) - (mu)), 2);
	}
	sigma = sqrt(((sigma) / 10000));
	empty.push_back(mu);
	empty.push_back(sigma);
	return empty;
}

double worstReturn(double sigma1, double sigma2, double rho, int n)
{
	std::mt19937_64 gen;
	std::normal_distribution<double> dist1(0, 1);
	std::normal_distribution<double> dist2(0, 1);

	double ret = 0.0;
	for (int i = 0; i < n; i++)
	{
		double a = dist1(gen);
		double empty = dist2(gen);
		double b = (rho * a) + sqrt(1 - ((rho)*(rho)))*empty;
		double mu1 = 0.0;
		double mu2 = 0.0;

		double A = mu1+ (sigma1 * a);
		double B = mu2+ (sigma2 * b);
		if (A > B)
		{
			ret += B;
		}
		else
			ret += A;
	}
	return ret/n;
}

double NormalDist::cdf(double x)
{
	double v = (x - mu_) / sigma_;
	return 0.5 * erfc(-v * M_SQRT1_2);
}

double NormalDist::invcdf(double prob)
{

	double left = mu_ - (3 * sigma_);
	double right = mu_ + (3 * sigma_);
	double empty = 0.0;
	double e = 1;

	if (prob < cdf(left))
		return left;
	else if (prob > cdf(right))
		return right;
	do
	{
		empty = (left + right) / 2;
		e = prob-cdf(empty);
		if (prob < cdf(empty))
		{
			right = empty;
		}
		else if (prob >cdf(empty))   
		{
			left = empty;
		}
	} while (abs(e) > 1e-8);


	return empty;
}

double PlanA::billingAmt(double usage)
{
	return base_+(unitCharge_ *usage);
}

double PlanB::billingAmt(double usage)
{
	double buff = 0.0;
	for (int i = 1; i < sections_.size(); i++)
	{
		//if (sections_[i]>usage>sections_[i-1])
		//{
		//	buff += additionalCharges_[i-1];
		//}
		if (usage<sections_[i] && usage>sections_[i - 1]) {
			buff += additionalCharges_[i - 1];
		}
	}
	if (usage > sections_[sections_.size() - 1])
		buff += additionalCharges_[sections_.size() - 1];
	return base_ + buff;
}


bool DataBill::compareWith(DataBill* plans,double usages)
{
	if (billingAmt(usages) > plans->billingAmt(usages))
	{
		return false;
	}
	else
		return true;

}
