#pragma once
#include <iostream>
#include <vector>
#include "date.h"

class TermStructure {
public:
	TermStructure(std::vector<Date> dates, std::vector<double> values) :
		dates_(dates), values_(values) {}
	~TermStructure() {}
	virtual double value(Date d);  //�տ��ٰ� virtual�� ���̸� �������̵��� �ȴ�! �ڽ�Ŭ�������� �������ϸ�, �ڽ��Լ����� ���.. ���蹮���� �� ���´�! 


protected: //����� ��, �ܺο��� �������� ������ �ڽ� Ŭ�������� �����ִ�!!
	double timeFromRef(Date d) {
		return daysBetween(dates_[0], d) / 365.0; //��¥�� �ð����� �ٲ۴�.. ù��° ��¥���� �Է��� ��¥������ �ð��� �������
	}

private:
	std::vector<Date> dates_;
	std::vector<double> values_;

};


//TermStructure���� ��ӹ޴´ٴ� �ǹ���.. private �Ǵ� protect ����� �� ���� �����ϱ� public ����ض�
class YieldTermStructure :public TermStructure {
public:  //Ŭ�������� �����ڰ� �� �־���Ѵ�!
	YieldTermStructure(std::vector<Date> date, std::vector<double> rates) :  //�ݷ�!!
		TermStructure(date, rates) {} //�θ�Ŭ������ �Ѱ�����Ѵ�!!
	double df(Date d);
	double fwd(Date d1, Date d2);
};

class VolTermStructure :public TermStructure {
public:
	VolTermStructure(std::vector<Date> date, std::vector<double> vol) :
		TermStructure(date, vol) {}
	double totalVariance(Date d);
	double value(Date d) { return 0.1; } //VolTermStructure �Լ������� ������ 0.1�� ��ȯ�ϴ� �Լ��� �ȴ�!! ���� �̷��� �������� �ʾҴٸ� �θ��Լ������� value�Լ��� ������!! Overriding�̶�� �θ�


};