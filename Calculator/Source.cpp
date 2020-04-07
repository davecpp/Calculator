#include <iostream>
#include <iterator>
#include "Calculator.h"
#include "RPNconverter.h"
using std::cout;
using std::endl;

#include <vector>

#include "RCalculator.h"

struct Coordinate {
	double x;
	double y;
};


std::vector<Coordinate> drawFunction(const std::string& expr, double _min, double _max, double delta) {
	std::vector<Coordinate> Ret;
	try {
		/*RPNCalculator::Converter conv;*/
		auto s = RPNCalculator::Converter::Converte(expr);
		RPNCalculator::RPNCalculator rc;

		decltype(s)::iterator it = s.begin();
		std::vector<decltype(s)::iterator> abscis_x;
		for (auto it = s.begin(); it != s.end(); ++it) {
			if (*it == "x")
				abscis_x.push_back(it);
		}


		for (double i = _min; i < _max; i += delta)
		{
			for (auto it = abscis_x.begin(); it != abscis_x.end(); ++it)
			{
				*(*it) = std::to_string(i);
			}
			Coordinate a; a.x = i;
			a.y = rc.Calculate(s.begin(), s.end());
			Ret.push_back(a);
		}
	}
	catch (const std::exception & ex) {
		cout << ex.what() << endl;
	}
	return Ret;
}


int masdain() {


	RPNCalculator::RPNCalculator c;
	std::string expr = "x^2+2*2+8.2-x*(3+7)+x^x";
	//std::cin >> expr;
	try {

		/*RPNCalculator::Converter conv;
		auto s = conv.To_postfix(expr);*/
		//auto s = RPNCalculator::inToPost(expr);

		//RPNCalculator::RPNCalculator c;

		std::vector<Coordinate> vc = drawFunction(expr,-20,20,0.01);

		//int k;

		//Calculator::RCalculator rc;
		//rc.To_Primitive(expr);
		//auto s = rc.l;

		/*for (const auto it : s) {
			cout << it << endl;
		}*/

	}
	catch (const std::exception & ex) {
		cout << ex.what() << endl;
	}


	//try {
	//	using separator = token_function::qchar_separator<RPNCalculator::t_string::value_type>;
	//	using tokenizer = boost::tokenizer<separator>;
	//	tokenizer tok{ expr,separator(" /t","+-*/","()") };

	//	for (const auto& it : tok) {
	//		cout << it << endl;
	//	}
	//}
	//catch (const std::exception& ex) {
	//	cout << ex.what() << endl;
	//};



	//2 3 * 5 8 - 7 + //6 -3 7 +
	//std::vector<std::string> v{ "2","3","*","5","8","-","7","*","+" };


	//cout << c.Calculate(v.begin(), v.end()) << endl;

	return 5;
}