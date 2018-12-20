
#include <cmath>
#include "analytic bs.h"
#include "normal.h"

double bsprice(double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type) {

	double d1 = (log(s / k) + (r - q + 0.5*sigma*sigma)*t) / (sigma*sqrt(t));
	double d2 = d1 - sigma * sqrt(t);
	double nd1 = normcdf(type*d1);
	double nd2 = normcdf(type*d2);
	double price = type * (s*exp(-q * t)*nd1 - k * exp(-r * t)*nd2);
	return price;
}

double bsd1(double s, double k, double r, double q, double sigma, double t) {
	double d1 = (log(s / k) + (r - q + 0.5*sigma*sigma)*t) / (sigma*sqrt(t));
	return d1;
}

double bsvega(double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type) {

	double d1 = (log(s / k) + (r - q + 0.5*sigma*sigma)*t) / (sigma*sqrt(t));
	double vega = s * exp(-q * t)*normpdf(d1)*sqrt(t);
	return vega;
}

double bsiv(double s, double k, double r, double q, double t, double price, OptionType type, double init, double tol)
{
	double e = 1;  //아직은 수렴 안 했다는 걸 알 정도의 크기로..
	double vol = init;
	while (abs(e) > tol)
	{
		e = price - bsprice(s, k, r, q, t, vol, type);
		vol = vol + e / bsvega(s, k, r, q, t, vol, type);
	}
	return vol;
}

double bsdelta(double d1,
	double q,
	double t,
	OptionType type) {
	double delta = type * exp(-q * t)*normcdf(type*d1);
	return delta;
}

double bstheta(double d1,
	double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type) {
	double d2 = d1 - sigma * sqrt(t);
	double theta = (-exp(-q * t)*s*sigma*normpdf(d1) / (2 * sqrt(t))) - (type*r*k*exp(-r * t)*normcdf(type*d2)) + (type*q*s*exp(-q * t)*normcdf(type*d1));
	return theta;
}

double bsrho(double d1,
	double k,
	double r,
	double t,
	double sigma, 
	OptionType type) {
	double d2 = d1 - sigma * sqrt(t);
	double rho = type * k*t*exp(-r * t)*normcdf(type*d2);
	return rho;
}

double bspsi(double d1,
	double s,
	double t,
	double q,
	OptionType type) {
	double psi = -type * s*t*exp(-q * t)*normcdf(type*d1);
	return psi;
}

double bsgamma(double d1,
	double s,
	double sigma,
	double t,
	double q,
	OptionType type) {
	double gamma = exp(-q * t)*normpdf(d1) / (s*sigma*sqrt(t));
	return gamma;
}

double bisectioniv(double s, double k, double r, double q, double t, double price, OptionType type, double left, double right, double tol)
{
	double vol = 0.0;
	double e = 1;  //아직은 수렴 안 했다는 걸 알 정도의 크기로..
	do
	{
		vol = (left + right) / 2;
		e = price - bsprice(s, k, r, q, t, vol, type);
		if (price< bsprice(s, k, r, q, t, vol, type))
		{
			right = vol;
		}
		if (price> bsprice(s,k,r,q,t,vol,type))    //옵션가격은 음수가 될 수 없으므로... 기울기도 항상 양수니까 부호 비교를 잘 선정해야한다. 인터넷에 있는거 아무거나 긁어오지말고..
		{
			left = vol;
		}
	} while (abs(e)>tol);
	return vol;
}