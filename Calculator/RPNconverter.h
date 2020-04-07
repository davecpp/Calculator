#pragma once

#include <string>
#include <stack>
#include <string_view>

#include "Typedefs.h"

#include <deque>

BEGIN_NAMESPACE(RPNCalculator)


enum class operations :int8_t {
	NON = '0',

	add = '+',
	sub = '-',
	mull = '*',
	div = '/',
	pow = '^',
	modul = '%',

	opener = '(',
	closer = ')',

	//unary operations
	//sin = 'operations_stack',
	//cos = 'c',

};




class Converter {
public:


	template<class Container_t = std::deque<t_string>>
	static Container_t Converte(t_string line) {//decltype(auto) = string_view
		/*using char_t = typename t_string::value_type;*/


		Container_t l;
		separator sep{ Spaces,m_Operations };
		tokenizer tok(line, sep);
		auto it = tok.begin();
		Converte(l, it);


		return l;
	}


private:
	inline static constexpr const char* m_Operations = "+-*/^%()";




	template<class Container_t, class Iterator>
	static inline void Converte(Container_t& l, Iterator& it) {
		std::stack<operations> operations_stack;
		auto to_op = [](const t_string& str) {
			auto it = op_map.find(str);
			return it == op_map.end() ? operations::NON : it->second;
		};

		if (*it == "-")
			l.push_back(*it++);

		while (!it.at_end())
		{

			if (Is_Value(*it))
				l.push_back(*it++);
			if (it.at_end()) {
				/*if (!operations_stack.empty())
					throw std::logic_error("invalid input");*/
				continue;
			}

			if (operations_stack.empty()) {
				operations_stack.push(to_op(*it++)); continue;
			}

			if (*it == ")") {
				while (operations_stack.top() != operations::opener) {
					l.push_back(t_string(i_op_map.find(operations_stack.top())->second));
					operations_stack.pop();
					if (operations_stack.empty())
						throw std::logic_error("invalid input ");
				}
				operations_stack.pop(); ++it; continue;
			}
			if (*it == "(") {
				operations_stack.push(to_op(*it++));
				if (*it == "-")
					l.push_back(*it++);
			}
			if (operations_stack.top() != operations::opener) {
				while (!operations_stack.empty() && priority(operations_stack.top()) >= priority(to_op(*it))) {
					l.push_back(t_string(i_op_map.find(operations_stack.top())->second));
					operations_stack.pop();
				}
				if (*it != ")")
					operations_stack.push(to_op(*it++));
			}
			else if (priority(to_op(*it)) > 0)
				operations_stack.push(to_op(*it++));

		}
		while (!operations_stack.empty())
		{
			l.push_back(t_string(i_op_map.find(operations_stack.top())->second));
			operations_stack.pop();
		}
		if (!operations_stack.empty())
			throw std::logic_error("invalid input");

	}


	static int priority(operations p) {
		switch (p) {
		case operations::add:
		case operations::sub:
			return 1;
		case operations::mull:
		case operations::div:
			return 2;
		case operations::pow:
			return 3;
		case operations::NON:
			return 0;
		default:
			return -1;
		}
	}

	inline static std::map<t_string, operations> op_map{
		std::make_pair("+",operations::add),
		std::make_pair("-",operations::sub),
		std::make_pair("*",operations::mull),
		std::make_pair("/",operations::div),
		std::make_pair("^",operations::pow),
		std::make_pair("%",operations::modul),

		std::make_pair("(",operations::opener),
		std::make_pair(")",operations::closer),

	};

	inline static std::map<operations, t_string> i_op_map{
		std::make_pair(operations::add,"+"),
		std::make_pair(operations::sub,"-"),
		std::make_pair(operations::mull,"*"),
		std::make_pair(operations::div,"/"),
		std::make_pair(operations::pow,"^"),
		std::make_pair(operations::modul,"%"),

		std::make_pair(operations::opener,"("),
		std::make_pair(operations::closer,")"),

	};

};





constexpr const char* m_Operations = "+-*/^%()";
class Converter2 {
	inline static std::map<t_string, operations> op_map{
				std::make_pair("+",operations::add),
				std::make_pair("-",operations::sub),
				std::make_pair("*",operations::mull),
				std::make_pair("/",operations::div),
				std::make_pair("^",operations::pow),
				std::make_pair("%",operations::modul),

				std::make_pair("(",operations::opener),
				//std::make_pair(")",operations::closer),

				//unary operations
				//std::make_pair("sin",operations::sin),
				//std::make_pair("cos",operations::cos),
	};

	inline static std::map<operations, t_string> i_op_map{
		std::make_pair(operations::add,"+"),
		std::make_pair(operations::sub,"-"),
		std::make_pair(operations::mull,"*"),
		std::make_pair(operations::div,"/"),
		std::make_pair(operations::pow,"^"),
		std::make_pair(operations::modul,"%"),

		std::make_pair(operations::opener,"("),
		//std::make_pair(operations::closer,")"),

		//unary operations
		//std::make_pair(operations::sin,"sin"),
		//std::make_pair(operations::cos,"cos"),
	};



	// to check if the input character 
	// is an operator or a '(' 
	static bool isOperator(const t_string& str)
	{
		return op_map.find(str) != op_map.end();
	}

	// to check if the input character is an operand 
	static bool isOperand(const t_string& str)
	{
		for (const auto ch : str) {
			if (!std::isdigit(ch) && ch != '.' && ch != 'x')
				return false;
		}
		return true;
	}

	static inline operations to_operator(const t_string& str) {

		auto it = op_map.find(str);
		return it == op_map.end() ? operations::NON : it->second;

	}

	static inline const t_string& op_to_str(operations op) {
		auto it = i_op_map.find(op);
		if (it == i_op_map.end())
			throw std::exception("error");
		return it->second;
	}
	// function to return precedence value 
	// if operator is present in stack 
	static int inPrec(operations input)
	{
		/*auto it = op_map.find(str);
		if (it == op_map.end())throw std::exception("error");
		operations input = it->second;*/
		switch (input) {
		case operations::add:
		case operations::sub:
			return 2;
		case operations::mull:
		case operations::modul:
		case operations::div:
			return 4;
		case operations::pow:
			return 5;
		case operations::opener:
			return 0;
		}
	}

	// function to return precedence value 
	// if operator is present outside stack. 
	static int outPrec(const t_string& str)
	{
		auto it = op_map.find(str);
		if (it == op_map.end())throw std::exception("error");
		operations input = it->second;
		switch (input) {
		case operations::add:
		case operations::sub:
			return 1;
		case operations::mull:
		case operations::modul:
		case operations::div:
			return 3;
		case operations::pow:
			return 6;
		case operations::opener:
			return 100;
		}
	}

	
	public:
	// function to convert infix to postfix 
	template<class Container_t = std::deque<t_string>>
	static Container_t Converte(const t_string& expression)
	{
		std::stack<operations> operations_stack;
		Container_t l;
		separator sep{ Spaces,m_Operations };
		tokenizer tok(expression, sep);
		auto it = tok.begin();
		// while input is not NULL iterate 
		while (!it.at_end()) {

			// if character an operand 
			if (isOperand(*it)) {
				l.push_back(*it);
			}

			// if input is an operator, push 
			else if (isOperator(*it)) {
				if (operations_stack.empty()
					|| outPrec(*it) > inPrec(operations_stack.top()))
					operations_stack.push(to_operator(*it));
				else {
					while (!operations_stack.empty()
						&& outPrec(*it) < inPrec(operations_stack.top())) {
						l.push_back(op_to_str(operations_stack.top()));
						operations_stack.pop();
					}
					operations_stack.push(to_operator(*it));
				}
			}

			// condition for opening bracket 
			else if (*it == ")") {
				while (operations_stack.top() != operations::opener) {
					l.push_back(op_to_str(operations_stack.top()));
					operations_stack.pop();
					// if opening bracket not present 
					if (operations_stack.empty())
						throw std::logic_error("invalid input");
				}

				// pop the opening bracket. 
				operations_stack.pop();
			}
			++it;
		}

		// pop the remaining operators 
		while (!operations_stack.empty()) {
			if (operations_stack.top() == operations::opener) {
				throw std::logic_error("invalid input");
			}
			l.push_back(op_to_str(operations_stack.top()));
			operations_stack.pop();
		}
		return l;
	}
};
END_NAMESPACE(RPNCalculator)
