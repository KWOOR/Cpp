#pragma once

enum OptionType { Call = 1, Put = -1 };

double bsprice(double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type);

double bsvega(double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type);

double bsiv(double s,
	double k,
	double r,
	double q,
	double t,
	double price,
	OptionType type,
	double init = 0.1,
	double tol = 1e-6);

double bsd1(double s, double k, double r, double q, double sigma, double t);

double bsdelta(double d1,
	double q,
	double t,
	OptionType type);

double bstheta(double d1,
	double s,
	double k,
	double r,
	double q,
	double t,
	double sigma,
	OptionType type);

double bsrho(double d1,
	double k,
	double r,
	double t,
	double sigma,
	OptionType type);

double bspsi(double d1,
	double s,
	double t,
	double q,
	OptionType type);

double bsgamma(double d1,
	double s,
	double sigma,
	double t,
	double q,
	OptionType type);


double bisectioniv(double s, double k, double r, double q, double t, double price, OptionType type, double left = -2, double right = 2, double tol=1e-6);
