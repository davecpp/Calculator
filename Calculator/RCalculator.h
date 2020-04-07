//#pragma once
//
//#include <string>
//#include <stack>
//#include <string_view>
//
//#include "Typedefs.h"
//#include "token_logic.h"
//#include "RPNconverter.h"
//#include "Calculator.h"
//#include <deque>
//
//BEGIN_NAMESPACE(Calculator)
//using t_string = RPNCalculator::t_string;
//
//using separator = token_function::qchar_separator<t_string::value_type>;
//using tokenizer = boost::tokenizer<separator>;
//
//constexpr const char* Spaces = " /t";
//constexpr const char* b_Operations = "+-*/^%";
//constexpr const char* quotes = "()";
//
//
//template<class Container_t = std::deque<t_string>>
//class RCalculator {
//public:
//	Container_t l;
//
//
//	void To_Primitive(const t_string& line) {
//		if (Is_PrimitiveExpression(line)) {
//			RPNCalculator::Converter conv;
//			RPNCalculator::RPNCalculator calc;
//			const auto& cont = conv.To_postfix(line);
//			l.push_back(boost::lexical_cast<t_string>(
//				calc.Calculate(cont.begin(), cont.end())));
//			return;
//		}
//		separator sep{ Spaces,b_Operations, quotes };
//		tokenizer tok(line, sep);
//		tokenizer::iterator it = tok.begin();
//
//
//		while (!it.at_end()) {
//			if (Is_PrimitiveExpression(*it)) {
//				l.push_back(*it++); continue;
//			}
//			else {
//				if ((*it).front() != '(' && (*it).back() != ')')
//					throw std::logic_error("invalid input");
//				To_Primitive((*it).substr(1, (*it).size() - 2));
//				++it;
//			}
//		}
//		return;
//	}
//
//private:
//
//	static const t_string primitive(Container_t& l, tokenizer::iterator& it) {
//		if (Is_PrimitiveExpression(*it))
//		{
//
//		}
//	}
//
//
//	static bool Is_PrimitiveExpression(const t_string& str) {
//		return str.find('(') == t_string::npos && str.find(')') == t_string::npos;
//	}
//
//};
//
//
//
//
//END_NAMESPACE(Calculator)