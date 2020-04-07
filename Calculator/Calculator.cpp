#include "Calculator.h"
#include <cmath>
#include <exception>


BEGIN_NAMESPACE(RPNCalculator)

opmap RPNCalculator::operations{
	{"+",[](op_type l,op_type r) {return l + r; }},
	{"-",[](op_type l,op_type r) {return l - r; }},
	{"*",[](op_type l,op_type r) {return l * r; }},
	{"/",[](op_type l,op_type r) {return l / r; }},
	{"%",[](op_type l,op_type r) {return std::fmod(l,r); }},
	{"^",[](op_type l,op_type r) {return std::pow(l,r); }},
};



op_type RPNCalculator::Calculate(const t_string& expr)
{
	separator sep{ Spaces, Operations };
	tokenizer tok{ expr,sep };
	return Calculate(tok.begin(), tok.end());
}

op_type RPNCalculator::pop_stack()
{
	auto ret = values.top();
	values.pop();
	return ret;
}//NRVO


void RPNCalculator::do_operation(const t_string& it)
{
	try {
		const auto& op{ operations.at(it) };
		const op_type r = pop_stack();
		const op_type l = pop_stack();
		const op_type result{ op(l,r) };
		values.push(result);
	}
	catch (const std::out_of_range&) {
		throw std::invalid_argument(it);
	}
}






END_NAMESPACE(RPNCalculator)


