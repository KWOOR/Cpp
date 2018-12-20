#pragma once
#include <iostream>
#include <vector>
#include "date.h"

class TermStructure {
public:
	TermStructure(std::vector<Date> dates, std::vector<double> values) :
		dates_(dates), values_(values) {}
	~TermStructure() {}
	virtual double value(Date d);  //앞에다가 virtual을 붙이면 오버라이딩이 된다! 자식클래스에서 재정의하면, 자식함수꺼를 써라.. 시험문제에 꼭 나온다! 


protected: //상속할 때, 외부에는 보여주지 않지만 자식 클래스에는 보여주는!!
	double timeFromRef(Date d) {
		return daysBetween(dates_[0], d) / 365.0; //날짜를 시간으로 바꾼다.. 첫번째 날짜에서 입력한 날짜까지의 시간을 계산해줌
	}

private:
	std::vector<Date> dates_;
	std::vector<double> values_;

};


//TermStructure에서 상속받는다는 의미임.. private 또는 protect 상속은 쓸 일이 없으니까 public 상속해라
class YieldTermStructure :public TermStructure {
public:  //클래스에는 생성자가 꼭 있어야한다!
	YieldTermStructure(std::vector<Date> date, std::vector<double> rates) :  //콜론!!
		TermStructure(date, rates) {} //부모클래스에 넘겨줘야한다!!
	double df(Date d);
	double fwd(Date d1, Date d2);
};

class VolTermStructure :public TermStructure {
public:
	VolTermStructure(std::vector<Date> date, std::vector<double> vol) :
		TermStructure(date, vol) {}
	double totalVariance(Date d);
	double value(Date d) { return 0.1; } //VolTermStructure 함수에서는 무조건 0.1을 반환하는 함수가 된다!! 만약 이렇게 선언하지 않았다면 부모함수에서의 value함수를 쓰겠지!! Overriding이라고 부름


};