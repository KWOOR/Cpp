#include "test.h"
#include <iostream>
#include <string>

int main() {
	//Problem 1
	for (int i = 2012; i <= 2020; ++i) {
		WeekDay w = weekday(i, 3, 17); //매년 3월 17일의 요일은?
		if (w == Sat || w == Sun)
			std::cout << i << ": Weekend" << std::endl;
		else if (w == Mon || w == Tue || w == Wed || w == Thu || w == Fri)
			std::cout << i << ": Weekday" << std::endl;
		else
			std::cout << "ERROR" << std::endl;
	}
	std::cout << std::string(40, '=') << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////
	//Problem 2
	for (int i = 10; i <= 50; i += 10) {
		std::vector<double> x = distance(i);  //10회~50회 까지 움직일 때 원점으로부터 거리
		printf("%3d : mean = %5.2f | std = %5.2f\n", i, x[0], x[1]);
	}
	std::cout << std::string(40, '=') << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	//Problem 3
	for (int i = -5; i <= 5; i += 5) {
		double rho = i / 10.0;
		double m = worstReturn(0.1, 0.12, rho);  //상관계수가 바뀔 때 worst return의 평균
		printf("%3.1f => %6.3f\n", rho, m);
	}
	printf("%3.1f => %6.3f\n", 1.0, worstReturn(0.1, 0.12, 1.0, 30000));
	std::cout << std::string(40, '=') << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	////Problem 4
	NormalDist d(0, 1);
	std::cout << "prob(z<1) = " << d.cdf(1.0) << "\t";
	std::cout << "inv = " << d.invcdf(d.cdf(1.0)) << std::endl;
	NormalDist n(5, 3);
	for (int i = 0; i <= 10; i += 2) {
		double p = i / 10.0;  //누적확률이 0 ~ 1 사이 0.2 간격으로
		printf("%3.1f : %8.5f\n", p, n.invcdf(p));
	}
	std::cout << std::string(40, '=') << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	////Problem 5
	std::vector<DataBill*> plans;
	//PlanB 인풋
	//2,000MB초과:기본료+10,000 | 5,000MB초과:기본료+20,000 | 10,000MB초과:기본료+30,000
	std::vector<double> sections = { 2000, 5000, 10000 };
	std::vector<double> additionalCharge = { 10000, 20000, 30000 };

	plans.push_back(new PlanA(10000, 5));     //기본료 10,000 + MB당 5
	plans.push_back(new PlanA(20000, 2.5));   //기본료 20,000 + MB당 2.5
	plans.push_back(new PlanB(25000, sections, additionalCharge)); //기본료 25,000

	std::vector<double> usages = { 500,4000,15000 };  //사용량에 대해서 각 plan별로 요금 계산
	for (unsigned int i = 0; i < plans.size(); ++i) {
		std::cout << "Plan " << i << " :" << std::endl;
		for (unsigned int j = 0; j < usages.size(); ++j) {
			std::cout << usages[j] << "MB = "
				<< plans[i]->billingAmt(usages[j]) << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::string(40, '=') << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////
	//Problem 6
	//기본료 30,000 + MB당 1.2 인 요금제를 위의 3가지 요금제와 비교
	PlanA myPlan(30000, 1.2);
	for (unsigned int i = 0; i < plans.size(); ++i) {
		std::cout << "Plan " << i << " :" << std::endl;
		for (unsigned int j = 0; j < usages.size(); ++j) {
			bool ec = myPlan.compareWith(plans[i], usages[j]);
			if (ec)
				std::cout << "Cheap / ";
			else
				std::cout << "Expensive / ";
		}
		std::cout << std::endl;
	}


	for (unsigned int i = 0; i < plans.size(); ++i)
		delete plans[i];
	////////////////////////////////////////////////////////////////////////////////////
	return 0;
}