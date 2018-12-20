#pragma once
#include "date.h"
#include <vector>
#include <ctime>

class TermStructure {
public: TermStructure(std::vector<Date> dates, std::vector<double> rates):dates_(dates), rates_(rates) {};
		~TermStructure() {};
		std::vector<Date> dates() { return dates_; }
		std::vector<double> rates() { return rates_; }
		double value(Date d);
protected:
	double timeFromRef(Date d) {return daysBetween(dates_[0], d) / 365.0;

private: std::vector<Date> dates_;
		 std::vector<double> rates_;
};



	class YieldTermStructure : public TermStructure {
	public:
		YieldTermStructure(std::vector<Date> date, std::vector<double> rates) :
			TermStructure(date, rates) {}
		double df(Date d);
		double fwd(Date d1, Date d2);
	};

	class VolTermStructure : public TermStructure {
	public:
		VolTermStructure(std::vector<Date> date, std::vector<double> vol) :
			TermStructure(date, vol) {}
		double totalVariance(Date d);
		double value(Date d) { return 0.1; }
	};