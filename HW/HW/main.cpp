#include <iostream>
#include "analytic bs.h"
#include "normal.h"  
#include "date.h"
#include <vector>
#include "TermSturcture.h"
#include <string>
#include "plainvanilla_option.h"
#include "gbmprocess.h"
#include "binary_option.h"



void print(Option* inst, double *ptr) {
	std::vector<double> greek;
	greek.push_back(inst->price());
	greek.push_back(inst->delta());
	greek.push_back(inst->gamma());
	greek.push_back(inst->vega());
	greek.push_back(inst->rho());
	greek.push_back(inst->theta());
	for (unsigned int i = 0; i < greek.size(); ++i)
	{
		printf("%7.2f|  ", greek[i]);
	}
	printf("\n");
	for (unsigned int i = 0; i < greek.size(); ++i)
	{
		ptr[i] += greek[i];
	}
}

void Optionpricing(GBMProcess process, std::vector<Date> mat, std::vector<double> k, std::vector<OptionType> type, Date evalDate, std::vector<std::string> kinds) {

	std::vector<Option*> products;
	for (int i = 0; i < 12; ++i) {
		if (kinds[i] == "v") {
			Option* inst = new PlainVanillaOption(mat[i], k[i], type[i]);
			products.push_back(inst);
		}
		else {
			Option* inst = new BinaryOption(mat[i], k[i], type[i]);
			products.push_back(inst);
		}

	}
	for (unsigned int i = 0; i < products.size(); ++i) {
		products[i]->setEvalDate(evalDate);
		products[i]->setProcess(process, evalDate);
	}
	int numgreek = 6;
	double* option_greek = new double[numgreek];

	for (int i = 0; i < numgreek; ++i)
	{
		option_greek[i] = 0;
	}
	printf(" No  | price |  delta  |  gamma  |   vega  |   rho   |  theta  | \n");


	for (unsigned int i = 0; i < products.size(); ++i) {
		printf(" %2d  |", i + 1);
		print(products[i], option_greek);

	}
	std::cout << std::string(63, '-') << std::endl;
	printf("합계 |%7.2f|%9.2f|%9.2f|%9.2f|%9.2f|%9.2f| \n", option_greek[0], option_greek[1], option_greek[2], option_greek[3], option_greek[4], option_greek[5]);
	for (unsigned int i = 0; i < products.size(); ++i) { // 모든 pointer를 delelte
		delete products[i];
	}
	delete[] option_greek;
}



int main() {

	std::cout << "Standard Normal Dist." << std::endl;
	for (int i = 0; i <= 20; ++i) {
		double x = i / 10.0 - 1.0;
		printf("%6.1f pdf = %0.4f, cdf = %0.4f\n", x, normpdf(x, 0, 1), normcdf(x, 0, 1));  
	}

	std::cout << "\nBlack-Scholes Prices\n";
	double k = 100, r = 0.02, q = 0.01, t = 0.25, vol = 0.2;
	for (int i = 0; i <= 20; ++i) {
		double s = 90 + i;
		double callPrice = bsprice(s, k, r, q, t, vol, Call);
		double putPrice = bsprice(s, k, r, q, t, vol, Put);
		double vega = bsvega(s, k, r, q, t, vol, Call);
		printf("S = %6.0f | Call = %8.3f | Put = %8.3f\n | vega=%6.2f\n", s, callPrice, putPrice, vega);
	}

	double optionprice = 3.0;
	double iv = bsiv(100, k, r, q, t, optionprice, Call);
	std::cout << "IV = " << iv << std::endl;
	for (int i = 0; i < 30; ++i)
		{
			double vol = (i + 1) / 100.0;//100이라고만 쓰면 안 된다. 
			std::cout << vol << ":" << bsprice(100, k, r, q, t, vol, Call) << std::endl;
		}
	std::cout << "OptionPrice = " << bsprice(100, k, r, q, t, iv, Call) << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 주가 100이라고 가정, sigma는 위에서 구한 내재변동성으로 가정
	double d1 = bsd1(100, k, r, q, iv, t);
	int s = 100;
	double delta = bsdelta(d1, q, t, Call);
	double theta = bstheta(d1, 100, k, r, q, t, iv, Call);
	double rho = bsrho(d1, k, r, t, iv, Call);
	double psi = bspsi(d1, s, t, q, Call);
	double gamma = bsgamma(d1, s, iv, t, q, Call);


	std::cout << gamma << std::endl;


	double biiv =bisectioniv(s,k,r,q,t,optionprice,Call);
	std::cout << "IV = " << biiv << std::endl;
	for (int i = 0; i < 30; ++i)
	{
		double vol = (i + 1) / 100.0;//100이라고만 쓰면 안 된다. 
		std::cout << vol << ":" << bsprice(100, k, r, q, t, vol, Call) << std::endl;
	}
	std::cout << "OptionPrice = " << bsprice(100, k, r, q, t, biiv, Call) << std::endl;


	///////////////////////////////////////////////////////TermStructure 구하는 예시/////////////////////////////////////
	std::vector<Date> d = { Date(2019, 01, 28), Date(2019,02,28) };
	std::vector<double> xx = { 0.5 , 0.7};
	TermStructure x(d,xx );
	TermStructure y(std::vector<Date>  { Date(2000,01,28), Date(2001,01,29), Date(2002,03,05) }, std::vector<double>   { 0.1, 1.3, 1.9 });
	double val=x.value(Date(2019,02,15));
	double valu = y.value(Date(2003, 01, 12));
	std::cout << val<<"\t" <<valu << std::endl;






	std::vector<Date> dates = { Date(2018,9,30), Date(2018,10,30), Date(2018,11,30), Date(2018,12,30), Date(2019,1,30), Date(2019, 2, 28), Date(2019, 3, 30), Date(2019, 4, 30) };
	Date evalDate(2018, 9, 30);
	double spot = 200;
	std::vector<double> rf = { 0.015, 0.015, 0.017, 0.0185, 0.0195, 0.0205, 0.0213, 0.022 }, div = { 0.0, 0.0, 0.0, 0.03, 0.03, 0.03, 0.04, 0.04 }, vol = { 0.1, 0.11, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145 };
	GBMProcess process(spot, rf, div, vol, dates);
	std::vector<std::string> kinds = { "v","v","v","v","v","v","b","b","b" ,"b" ,"b" ,"b" };
	std::vector<int> position = { 1, -1,1,-1,-1,1,-1,1,-1,1,1,-1 };
	std::vector<OptionType> type = { Call, Call, Call, Put, Put,Put,Call, Call, Put,Put,Put,Call, };
	std::vector<double> k = { 200, 205,195,200,210,190,200,220,200,210,190,205 };
	std::vector<Date> mat = { Date(2019,1,10), Date(2018, 12, 12), Date(2019, 3, 15), Date(2018, 12, 12), Date(2019, 3, 15), Date(2019, 1, 10),
										 Date(2018, 11, 25), Date(2019, 3, 20), Date(2019, 2, 18), Date(2018, 12, 19), Date(2019, 1, 15), Date(2019, 2, 25) };





	Optionpricing(process, mat, k, type, evalDate, kinds);
	std::cout << "\n" << "주가가 10% 상승한 경우" << std::endl;;
	GBMProcess process2(spot*1.1, rf, div, vol, dates);
	Optionpricing(process2, mat, k, type, evalDate, kinds);

	std::cout << "\n" << "주가가 10% 하락한 경우" << std::endl;;
	GBMProcess process3(spot*0.9, rf, div, vol, dates);
	Optionpricing(process3, mat, k, type, evalDate, kinds);
	printf("\n\n");
	std::vector<Option*> products;
	for (int i = 0; i < 6; ++i) {
		Option* inst = new PlainVanillaOption(mat[i], k[i], type[i]);
		products.push_back(inst);
	}
	double change_greek[6][6];
	double change_data[6][6];

	for (unsigned int i = 0; i < products.size(); ++i) {
		products[i]->setEvalDate(evalDate);
		products[i]->setProcess(process, evalDate);
		double delta = products[i]->delta();
		double gamma = products[i]->gamma();
		double vega = products[i]->vega();
		double rho = products[i]->rho();
		double ds = spot * 0.01;
		change_greek[i][0] = delta * ds + 0.5 * gamma * ds * ds;
		change_greek[i][1] = delta * -ds + 0.5 * gamma * -ds * -ds;

		double dvol = process.getVol(evalDate)*0.01;
		change_greek[i][2] = vega * dvol;
		change_greek[i][3] = vega * -dvol;

		double dr = 0.001;
		change_greek[i][4] = rho * dr;
		change_greek[i][5] = rho * -dr;

		change_data[i][0] = products[i]->price_change(ds = ds, 0, 0) - products[i]->price();
		change_data[i][1] = products[i]->price_change(ds = -ds, 0, 0) - products[i]->price();
		change_data[i][2] = products[i]->price_change(0, dvol, 0) - products[i]->price();
		change_data[i][3] = products[i]->price_change(0, -dvol, 0) - products[i]->price();
		change_data[i][4] = products[i]->price_change(0, 0, dr) - products[i]->price();
		change_data[i][5] = products[i]->price_change(0, 0, -dr) - products[i]->price();

	}

	int n = 0;
	do {
		printf("Assignment #1 가격변동을 확인하고 싶은 번호를 입력하세요(1~6)");
		std::cin >> n;
		if (n >= 1 && n <= 6)
		{
			break;
		}
		printf("(1~6)사이의 숫자를 입력하세요.\n");
	} while (n < 1 || n > 6);

	printf("  시나리오 | 가격 변동 |Greek으로 계산한 가격변동| 오차 \n");
	printf("  주가 +1%% |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][0], change_greek[n - 1][0], change_data[n - 1][0] - change_greek[n - 1][0]);
	printf("  주가 -1%% |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][1], change_greek[n - 1][1], change_data[n - 1][1] - change_greek[n - 1][1]);
	printf("변동성 +1%% |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][2], change_greek[n - 1][2], change_data[n - 1][2] - change_greek[n - 1][2]);
	printf("변동성 -1%% |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][3], change_greek[n - 1][3], change_data[n - 1][3] - change_greek[n - 1][3]);
	printf("금리 +10bp |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][4], change_greek[n - 1][4], change_data[n - 1][4] - change_greek[n - 1][4]);
	printf("금리 -10bp |   %6.3f  |	%10.3f 	 |%6.3f\n", change_data[n - 1][5], change_greek[n - 1][5], change_data[n - 1][5] - change_greek[n - 1][5]);

	std::cout << std::string(63, '-') << std::endl;
	for (int i = 0; i < 6; i++)
	{
		double newton = products[i]->impliedVol(products[i]->price());
		double bi = products[i]->impliedVol_bisection(products[i]->price());
		printf("%d번 옵션 Newton-Raphson 방법 ivol은 %5.3f, Bisection 방법 ivol 은 %5.3f, 두 방법간 차이는 %7.3f 입니다.\n", i + 1, newton, bi, newton - bi);
	}


	for (unsigned int i = 0; i < products.size(); ++i) { delete products[i]; }


	std::cin.get();
	return 0;
}

